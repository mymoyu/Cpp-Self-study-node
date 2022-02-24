#### 性能下降SQL慢 - 执行时间长 - 等待时间长

1. 查询语句问题

2. 索引失效 -------单值

   ​				  |----复合

3. 关键查询太多 join(设计缺陷或有不得已的需求)

4. 服务器调优及各个参数设置(缓冲, 线程数等)



建单值索引的命令:  create index idx_user_name on table_name(name1);

建立复合索引的命令: create index idx_user_name on table_name(name1, name2);

#### 常用的Join查询

##### 手写

```sql
SELECT DISTINCT <select_list> 
FROM <left_table> <join_type> 
JOIN <right_table> ON <join_condition>
WHERE <where_condition>
GROUP BY <group_by_list>
HAVING <having_condition>
ORDER BY <order_by_condtion>
LIMIT <limit_number>
```

##### 机读

```sql
FROM <left_table>  [笛卡尔积]
ON <join_condition> <join_type> [主表保留]
JOIN <right_table> [不符合ON也添加]
WHERE <where_condition> [非聚合 - 非SELECT别名]
GROUP BY <group_by_list>  [改变对表索引]
HAVING <having_condition> [只作用分组后]
SELECT 					   [DISTINCT]
DISTINCT <select_list>
ORDER BY <order_by_condtion> [可使用SELECT 别名]
LIMIT <limit_number>		[rows - offset]
```



#### 七种理论

###### A圆和B圆重叠的部分

```sql
SELECT <select_list> FROM TableA INNER JOIN TableB ON A.key = B.key
```

###### A圆的全部不包含B圆(但包含重叠部分)

```sql
SELECT <select_list> FROM TableA LEFT JOIN TableB ON A.key = B.key
```

###### B圆的全部不包含A圆(但包含重叠部分)

```sql
SELECT <select_list> FROM TableA RIGHT JOIN TableB ON A.key = B.key
```

###### A圆的全部不包含B圆, 并减去重叠部分

```sql
SELECT <select_list> 
FROM TableA LEFT JOIN TableB 
ON A.key = B.key
WHERE B.key IS NULL 
[此时的key因为被A独占而没有, 故IS NULL是去掉公有部分, 因为此时的B.key对应为空]
[B的key是NULL说明B没有对应连上的key, 而A有]
```

###### B圆的全部不包含A圆, 并减去重叠部分

```sql
SELECT <select_list> 
FROM TableA RIGHT JOIN TableB 
ON A.key = B.key
WHERE A.key IS NULL 
[此时的key因为被A独占而没有, 故IS NULL是去掉公有部分]
[B的key是NULL说明B没有对应连上的key, 而A有]
```

###### A和B圆都包含[全连接]

```sql
SELECT <select_list> FROM TableA FULL OUTER JOIN TableB ON A.key = B.key
```

###### A独有的部分和B圆独有的部分(不包含重叠部分)

```sql
SELECT <select_list> FROM TableA FULL OUTER JOIN TableB ON A.key = B.key
WHERE A.key IS NULL OR B.key IS NULL
```

##### 实际写法

由于mysql不支持full outer

###### 但是想要进行全连接可以使用union写法[将左右查询合并即可]

```sql
mysql> select * from tbl_emp a left join tbl_dept b on a.deptId = b.id 
    -> union 
    -> select * from tbl_emp a right join tbl_dept b on a.deptId = b.id
```

###### A独有的部分和B圆独有的部分(不包含重叠部分)可以写成

```sql
mysql> select * from tbl_emp a left join tbl_dept b on a.deptId = b.id 
	-> where b.id IS NULL
    -> union 
    -> select * from tbl_emp a right join tbl_dept b on a.deptId = b.id
    -> where b.id IS NULL
```

