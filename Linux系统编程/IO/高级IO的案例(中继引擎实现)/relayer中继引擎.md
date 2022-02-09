#### main.c

```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "relayer.h"

#define TTY1 "/dev/tty11"
#define TTY2 "/dev/tty12"
#define TTY3 "/dev/tty10"
#define TTY4 "/dev/tty9"

int main(void)
{
	int fd1, fd2, fd3, fd4;
	int job1, job2;

	fd1 = open(TTY1, O_RDWR);
	if(fd1 < 0)
	{
		perror("open()");
		exit(1);
	}
	write(fd1, "TTY1\n", 5);

	fd2 = open(TTY2, O_RDWR|O_NONBLOCK);
	if(fd2 < 0)
	{
		perror("open()");
		exit(1);
	}
	write(fd2, "TTY2\n", 5);

	job1 = rel_addjob(fd1, fd2);
	if(job1 < 0)
	{
		fprintf(stderr, "rel_addjob():%s\n", strerror(-job1));
		exit(1);
	}

	fd3 = open(TTY3, O_RDWR);
	if(fd3 < 0)
	{
		perror("open()");
		exit(1);
	}
	write(fd3, "TTY3\n", 5);

	fd4 = open(TTY4, O_RDWR);
	if(fd4 < 0)
	{
		perror("open()");
		exit(1);
	}
	write(fd4, "TTY4\n", 5);

	job2 = rel_addjob(fd3, fd4);
	if(job2 < 0)
	{
		fprintf(stderr, "rel_addjob():%s\n", strerror(-job1));
                exit(1);
	}

	while(1)
		pause();

	close(fd2);
	close(fd1);
	close(fd3);
	close(fd4);

	exit(0);
}
```



#### relayer.h

```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

#include "relayer.h"

#define BUFSIZE 1024

// 四种状态
enum
{
	STATE_R = 1,
	STATE_W,
	STATE_Ex, // 异常终止态
	STATE_T   // 终止态
};

struct rel_fsm_st
{
	int state; // 当前状态机状态
	int sfd;   // read
	int dfd;   // write
	char buf[BUFSIZE];
	int len;   // 读取的内容长度
	int pos;   // 数组的读取位置
	char *errstr;
	int64_t count;
};

struct rel_job_st
{
	int job_state;
	int fd1;
	int fd2;
	struct rel_fsm_st fsm12, fsm21;
	int fd1_save, fd2_save; // 由于后面是要复原的, 所以在结构体中保留这两个值
};

static struct rel_job_st* rel_job[REL_JOBMAX];
static pthread_mutex_t mut_rel_job = PTHREAD_MUTEX_INITIALIZER;
static pthread_once_t init_once = PTHREAD_ONCE_INIT;

static void fsm_driver(struct rel_fsm_st *fsm)
{
	int ret;
	// 每个状态各司其职, 不要状态跨越
	switch(fsm->state)
	{
		case STATE_R:
		{
			fsm->len = read(fsm->sfd, fsm->buf, BUFSIZE);
			if(fsm->len == 0)
			{
				fsm->state = STATE_T;
			}
			else if(fsm->len < 0)
			{
				if(errno == EAGAIN) // 读取阻塞造成的假错
					fsm->state = STATE_R;
				else
				{
					fsm->errstr = "read()";
					fsm->state = STATE_Ex;
				}
			}
			else
			{
				fsm->pos = 0;
				fsm->state = STATE_W;
			}
			break;
		}
		case STATE_W:
		{
			ret = write(fsm->dfd, fsm->buf+fsm->pos, fsm->len);
			if(ret < 0)
			{
				if(errno == EAGAIN)
					fsm->state = STATE_W;
				else
				{
					fsm->errstr = "write()";
					fsm->state = STATE_Ex;
				}
			}
			else
			{
				fsm->pos += ret; // 数组读取处上移动
				fsm->pos += ret;
				fsm->len -= ret;
				if(fsm->len)
					fsm->state = STATE_W;
				else
					fsm->state = STATE_R;
			}
			break;
		}
		case STATE_Ex:
		{
			perror(fsm->errstr);
			fsm->state = STATE_T;
			break;
		}
		case STATE_T:
		{
			/*do sth, as:clear*/
			break;
		}
		default:
		{
			abort();
			break;
		}
	}
}

static void* thr_relayer(void *p)
{
	int i;
	while(1)
	{
		pthread_mutex_lock(&mut_rel_job);
		for(i = 0; i < REL_JOBMAX; ++i)
		{
			if(rel_job[i] != NULL)
			{
				if(rel_job[i]->job_state == STATE_RUNNING)
				{
					fsm_driver(&rel_job[i]->fsm12);
					fsm_driver(&rel_job[i]->fsm21);
					// 如果两个状态都停了, 那么说明这两个状态机推完, 可以被销毁了
					if(rel_job[i]->fsm12.state == STATE_T && \
                                          rel_job[i]->fsm21.state == STATE_T )
						rel_job[i]->job_state = STATE_OVER;
				}
			}
		}
		pthread_mutex_unlock(&mut_rel_job);
	}
}

// modelue_unload()

// 创造一个作为状态机的线程
static void module_load(void)
{
	int err;
	pthread_t tid_relayer;

	err = pthread_create(&tid_relayer, NULL, thr_relayer, NULL);
	if(err)
	{
		fprintf(stderr, "pthread_create(): %s\n", strerror(err));
		exit(1);
	}
}

static int get_free_pos_unlocked()
{
	int i;
	for(i = 0; i < REL_JOBMAX; ++i)
	{
		if(rel_job[i] == NULL)
			return i;
	}

	return -1;
}

int rel_addjob(int fd1, int fd2)
{
	int pos; // 所在的指针数组下标
	struct rel_job_st *me;

	// 动态模块的单词初始化实现
	pthread_once(&init_once, module_load);

	me = malloc(sizeof(*me));
	if(me == NULL)
		return -ENOMEM;
	me->fd1 = fd1;
	me->fd2 = fd2;
	me->job_state = STATE_RUNNING;

	// 统一改为非阻塞
	me->fd1_save = fcntl(me->fd1, F_GETFL);
	fcntl(me->fd1, F_SETFL, me->fd1_save | O_NONBLOCK);
	me->fd2_save = fcntl(me->fd2, F_GETFL);
	fcntl(me->fd2, F_SETFL, me->fd2_save | O_NONBLOCK);

	me->fsm12.sfd = me->fd1;
	me->fsm12.dfd = me->fd2;
	me->fsm12.state = STATE_R;

	me->fsm21.sfd = me->fd2;
        me->fsm21.dfd = me->fd1;
        me->fsm21.state = STATE_R;

	pthread_mutex_lock(&mut_rel_job);
	pos = get_free_pos_unlocked();
	if(pos < 0)
	{
		pthread_mutex_unlock(&mut_rel_job);
		fcntl(me->fd1, F_SETFL, me->fd1_save);
		fcntl(me->fd2, F_SETFL, me->fd2_save);
		free(me);
		return -ENOSPC;
	}

	rel_job[pos] = me;

	pthread_mutex_unlock(&mut_rel_job);

	return pos; // 返回下标
}
// return >= 0          success, 返回当前任务id
//        == -EINVAL    error, 参数非法
//        == -ENOSPC    error, job array is empty
//        == -ENOMEM    error, memory allocation is incorrect

#if 0
int rel_canceljob(int id);
/*
 * return == 0          success, 指定任务被取消
 *        == -EINVAL    error, 参数非法
 *        == -EBUSY     error, 任务早已被取消
 */
int rel_waitjob(int id);
/*
 * return == 0          success, 指定任务已终止
 *        == -EINVAL    error, 参数非法
 */

int rel_statjob(int id, struct rel_stat_st *);
/*
 * return == 0           success, 指定任务状态已经返回
 *        == -EINVAL     error, 参数非g
 */
#endif
```



#### relayer.h

```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

#include "relayer.h"

#define BUFSIZE 1024

// 四种状态
enum
{
	STATE_R = 1,
	STATE_W,
	STATE_Ex, // 异常终止态
	STATE_T   // 终止态
};

struct rel_fsm_st
{
	int state; // 当前状态机状态
	int sfd;   // read
	int dfd;   // write
	char buf[BUFSIZE];
	int len;   // 读取的内容长度
	int pos;   // 数组的读取位置
	char *errstr;
	int64_t count;
};

struct rel_job_st
{
	int job_state;
	int fd1;
	int fd2;
	struct rel_fsm_st fsm12, fsm21;
	int fd1_save, fd2_save; // 由于后面是要复原的, 所以在结构体中保留这两个值
};

static struct rel_job_st* rel_job[REL_JOBMAX];
static pthread_mutex_t mut_rel_job = PTHREAD_MUTEX_INITIALIZER;
static pthread_once_t init_once = PTHREAD_ONCE_INIT;

static void fsm_driver(struct rel_fsm_st *fsm)
{
	int ret;
	// 每个状态各司其职, 不要状态跨越
	switch(fsm->state)
	{
		case STATE_R:
		{
			fsm->len = read(fsm->sfd, fsm->buf, BUFSIZE);
			if(fsm->len == 0)
			{
				fsm->state = STATE_T;
			}
			else if(fsm->len < 0)
			{
				if(errno == EAGAIN) // 读取阻塞造成的假错
					fsm->state = STATE_R;
				else
				{
					fsm->errstr = "read()";
					fsm->state = STATE_Ex;
				}
			}
			else
			{
				fsm->pos = 0;
				fsm->state = STATE_W;
			}
			break;
		}
		case STATE_W:
		{
			ret = write(fsm->dfd, fsm->buf+fsm->pos, fsm->len);
			if(ret < 0)
			{
				if(errno == EAGAIN)
					fsm->state = STATE_W;
				else
				{
					fsm->errstr = "write()";
					fsm->state = STATE_Ex;
				}
			}
			else
			{
				fsm->pos += ret; // 数组读取处上移动
				fsm->pos += ret;
				fsm->len -= ret;
				if(fsm->len)
					fsm->state = STATE_W;
				else
					fsm->state = STATE_R;
			}
			break;
		}
		case STATE_Ex:
		{
			perror(fsm->errstr);
			fsm->state = STATE_T;
			break;
		}
		case STATE_T:
		{
			/*do sth, as:clear*/
			break;
		}
		default:
		{
			abort();
			break;
		}
	}
}

static void* thr_relayer(void *p)
{
	int i;
	while(1)
	{
		pthread_mutex_lock(&mut_rel_job);
		for(i = 0; i < REL_JOBMAX; ++i)
		{
			if(rel_job[i] != NULL)
			{
				if(rel_job[i]->job_state == STATE_RUNNING)
				{
					fsm_driver(&rel_job[i]->fsm12);
					fsm_driver(&rel_job[i]->fsm21);
					// 如果两个状态都停了, 那么说明这两个状态机推完, 可以被销毁了
					if(rel_job[i]->fsm12.state == STATE_T && \
                                          rel_job[i]->fsm21.state == STATE_T )
						rel_job[i]->job_state = STATE_OVER;
				}
			}
		}
		pthread_mutex_unlock(&mut_rel_job);
	}
}

// modelue_unload()

// 创造一个作为状态机的线程
static void module_load(void)
{
	int err;
	pthread_t tid_relayer;

	err = pthread_create(&tid_relayer, NULL, thr_relayer, NULL);
	if(err)
	{
		fprintf(stderr, "pthread_create(): %s\n", strerror(err));
		exit(1);
	}
}

static int get_free_pos_unlocked()
{
	int i;
	for(i = 0; i < REL_JOBMAX; ++i)
	{
		if(rel_job[i] == NULL)
			return i;
	}

	return -1;
}

int rel_addjob(int fd1, int fd2)
{
	int pos; // 所在的指针数组下标
	struct rel_job_st *me;

	// 动态模块的单词初始化实现
	pthread_once(&init_once, module_load);

	me = malloc(sizeof(*me));
	if(me == NULL)
		return -ENOMEM;
	me->fd1 = fd1;
	me->fd2 = fd2;
	me->job_state = STATE_RUNNING;

	// 统一改为非阻塞
	me->fd1_save = fcntl(me->fd1, F_GETFL);
	fcntl(me->fd1, F_SETFL, me->fd1_save | O_NONBLOCK);
	me->fd2_save = fcntl(me->fd2, F_GETFL);
	fcntl(me->fd2, F_SETFL, me->fd2_save | O_NONBLOCK);

	me->fsm12.sfd = me->fd1;
	me->fsm12.dfd = me->fd2;
	me->fsm12.state = STATE_R;

	me->fsm21.sfd = me->fd2;
        me->fsm21.dfd = me->fd1;
        me->fsm21.state = STATE_R;

	pthread_mutex_lock(&mut_rel_job);
	pos = get_free_pos_unlocked();
	if(pos < 0)
	{
		pthread_mutex_unlock(&mut_rel_job);
		fcntl(me->fd1, F_SETFL, me->fd1_save);
		fcntl(me->fd2, F_SETFL, me->fd2_save);
		free(me);
		return -ENOSPC;
	}

	rel_job[pos] = me;

	pthread_mutex_unlock(&mut_rel_job);

	return pos; // 返回下标
}
// return >= 0          success, 返回当前任务id
//        == -EINVAL    error, 参数非法
//        == -ENOSPC    error, job array is empty
//        == -ENOMEM    error, memory allocation is incorrect

#if 0 // 之后完善
int rel_canceljob(int id);
/*
 * return == 0          success, 指定任务被取消
 *        == -EINVAL    error, 参数非法
 *        == -EBUSY     error, 任务早已被取消
 */
int rel_waitjob(int id);
/*
 * return == 0          success, 指定任务已终止
 *        == -EINVAL    error, 参数非法
 */

int rel_statjob(int id, struct rel_stat_st *);
/*
 * return == 0           success, 指定任务状态已经返回
 *        == -EINVAL     error, 参数非g
 */
#endif
```



#### makefile

```C
CFLAGS+=-pthread
LDFLAGS+=-pthread

all: relayer

relayer:relayer.o main.o
	gcc $^ -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o relayer
```

