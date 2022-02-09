##### makefile

```C
all:anytimer

anytimer:main.o anytimer.o
	gcc $^ -o $@

clean:
	rm -rf *.o anytimer
```



##### anytimer.h

```C
#ifndef ANYTIMER_H__
#define ANYTIMER_H__


#define JOB_MAX 1024

typedef void at_jobfunc_t(char *);

int at_addjob(int sec, at_jobfunc_t *jobp, void *arg);
/*
 * return >= 0        success
 *        == -EINVAL  error, invaalid argument
 *        == -ENOSPC  error, array is full
 *        == -ENOMEM  error, insufficient memory space
 */

int at_canceljob(int id);
/*
 * return == 0           sucess
 *        == -EINVAL     error, invaalid argument
 *        == -EBUSY      error, the specified task has been completed
 *        == -ECANCELED  error, the specified task was repeatedly canceled
 */

int at_waitjob(int id);
/*
 * return == 0           sucess
 *        == -EINVAL     error, invaalid argument
 */

#endif
```



##### anytimer.c

```C
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include "anytimer.h"

typedef void (*sighandler_t)(int);

static struct job* jobs[JOB_MAX];
static int inited = 0;
static sighandler_t alrm_handler_save;

struct job
{
	int sec;
	at_jobfunc_t *jobp; // get function
	void *arg;
	int pos; // postion
	int flag;
};

static int get_free_pos(void)
{
	int i;
	for(i = 0; i < JOB_MAX; ++i)
	{
		if(jobs[i] == NULL)
			return i;
	}

	return -1;
}

static void alrm_handler(int s)
{
	int i;
	alarm(1);
	for(i = 0; i < JOB_MAX; ++i)
	{
		if(jobs[i] != NULL)
		{
			(jobs[i]->sec)--;
			if((jobs[i]->sec) <= 0 && (jobs[i]->flag) == 1)
			{
				(*(jobs[i]->jobp))(jobs[i]->arg);
				jobs[i]->flag = 3;
                // 此处也可以用来销毁, 不过没必要
				//at_waitjob(i);
			}
		}
	}
}

static void module_unload(void)
{
	int i;
	signal(SIGALRM, alrm_handler_save);
	alarm(0);
	for(i = 0; i < JOB_MAX; ++i)
	{
		free(jobs[i]);
	}
}

static void module_load(void)
{
	alrm_handler_save = signal(SIGALRM, alrm_handler);
	alarm(1);

	atexit(module_unload);
}

int at_addjob(int sec, at_jobfunc_t *jobp, void *arg)
{
	struct job* newjob;
	int pos;

	if(!inited)
	{
		module_load();
		inited = 1;
	}

	pos = get_free_pos();
	if(pos < 0)
	{
		return -ENOSPC;
	}

	newjob = malloc(sizeof(*newjob));
	if(newjob == NULL)
	{
		return -ENOMEM;
	}

	newjob->sec = sec;
	newjob->jobp = jobp;
	newjob->arg = arg;
	newjob->pos = pos;
	newjob->flag = 1;

	jobs[pos] = newjob;

	return pos;
}

int at_canceljob(int id)
{
	if(id < 0 || id >= JOB_MAX)
		return -EINVAL;
	if(jobs[id] == NULL)
	{
		return -EBUSY;
	}
	if(jobs[id]->flag == 2)
	{
		return -ECANCELED;
	}
	jobs[id]->flag = 2;
	return 0;
}

// 任务完成, 销毁任务, 从数组里清除
int at_waitjob(int id)
{
	struct job *jobptr;
	if(id < 0 || id >= JOB_MAX)
                return -EINVAL;
	if(jobs[id] == NULL)
		return 0; // success
	
	if(jobs[id]->flag == 3)
	{
		jobptr = jobs[id];
		jobs[id] = NULL;
		free(jobptr);
		return 1; // also success
	}
	return 0;
}

```



##### main.c

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "anytimer.h"

static void f2(char *str)
{
	printf("f2: ");
	puts(str);
}

static void f1(char *str)
{
	printf("f1: ");
	puts(str);
}

int main(void)
{
	int job1, job2, job3;
	puts("Begin!");

	//5s, f1("aaa");
	job1 = at_addjob(5, f1, "aaa");
	if(job1 < 0)
	{
		fprintf(stderr, "at_addjob(): %s\n", strerror(-job1));
		exit(1);
	}
	//2s, f2("bbb");
	job2 = at_addjob(2, f2, "bbb");
	if(job2 < 0)
	{
		fprintf(stderr, "at_addjob(): %s\n", strerror(-job2));
		exit(1);
	}
	//7s, f1("ccc");
	job3 = at_addjob(7, f1, "ccc");
	if(job3 < 0)
        {
                fprintf(stderr, "at_addjob(): %s\n", strerror(-job3));
                exit(1);
        }

	puts("End!");

    // 此处有些略了, 如变量最好拆开, 而不是用一个, 此处目的是销毁无用的任务
	if((job1 = at_waitjob(job1)) < 0)
	{
		fprintf(stderr, "at_addjob(): %s\n", strerror(-job1));
		exit(1);
	}
	if((job2 = at_waitjob(job2)) < 0)
        {
                fprintf(stderr, "at_addjob(): %s\n", strerror(-job2));
                exit(1);
        }
	if((job3 = at_waitjob(job3)) < 0)
        {
                fprintf(stderr, "at_addjob(): %s\n", strerror(-job3));
                exit(1);
        }
	while(1)
	{
		write(1, ".", 1);
		sleep(1);
	}

	exit(0);
}

```

