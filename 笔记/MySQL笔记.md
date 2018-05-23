## 一、MySQL 基础
### 1、DDL语句
* DDL（Data Definition Languages）语句：数据定义语言，这些语句定义了不同的数据段、数据库、表、  列、  索引等数据库对象的定义。常用的语句关键字主要包括create、drop、alter等。


|Syntaxes                | Results |
|----                    |----      |
|CREATE DATABASE db_name | 创建数据库 |
|SHOW DATABASES/TABLES/COLUMNS | 显示所有数据库/表/字段 |
|USE db_name             | 选择要操作的数据库|
|SHOW TABLES             | 查看数据库中所有数据表|
|DROP DATABASE db_name   | 删除数据库|
|CREATE TABLE tb_name(c_name c_type contrains,...)   | 创建表，contrains为约束条件|
|DESC tb_name            | 查看表|
|SHOW CREATE TABLE tb_name \G| 查看创建表的SQL语句|
|DROP TABLE tb_name      | 删除表|
|ALTER TABLE tb_name RENAME new_name| 表改名|
|ALTER TABLE tb_name MODIFY c_name new_type| 修改字段的类型|
|ALTER TABLE tb_name ADD COLUMN c_name c_type| 表中添加字段|
|ALTER TABLE tb_name DROP COLUMN c_name| 删除表中字段|
|ALTER TABLE tb_name CHANGE o_c_name n_c_name n_type | 修改字段名和字段类型|


1. 控制台输入`mysql -uroot -p`，然后输入密码，进入mysql欢迎界面。
2. ADD添加字段默认添在表的最后位置，使用`ALTER TABLE tb_name ADD COLUMN c_name c_type (AFTER c_name/FIRST)`可以使新字段添在(`c_name`后/最前面)。该可选项也可以用在`CHANGE/MODIFY`中。

### 2、DML语句
* DML（Data Manipulation Language）语句：数据操纵语句，用于添加、删除、更新和查询数据库记录，并检查数据完整性，常用的语句关键字主要包括insert、delete、udpate和select等

|Syntaxes                | Results  |
|----                    | ----     |
|INSERT INTO tb_name c_list VALUES (value,...) | 向表中插入记录，可以不制定字段名，但value顺序要与字段排列一致|
|UPDATE tb_name SET c_name=n_value WHERE condition| 修改满足condition的所有记录|
|DELETE FROM tb_name WHERE condition| 删除记录，不加WHERE条件则删除表中所有记录|
|SELECT * FROM tb_name WHERE condition| 查询记录,WHERE条件可不加，*可改成一些字段名|
|SELECT c1_name,c2_name FROM tb1_name,tb2_name WHERE condition | 外连接查询表|
|SELECT...UNION (ALL) SELECT... | 合并查询出的记录，有ALL则去重|
|SELECT * FROM tb_name GROUP BY C_NAME HAVING condition | 将查询结果按某字段进行分组，值相等的为一组。|

1. 插入记录时，对于可空字段、非空但含有默认值的字段、自增字段，可以不在`INSERT`后的字段列表中出现，没写的自动设置为：NULL、默认值、自增的下一个数字。`INSERT VALUES`后可以一次性插入多条记录，用逗号隔开即可。
2. 更新记录时，可以同时更新多个表中的字段。用法：`UPDATE tb_name1  a,tb_name2 b SET a.c_name=n_value,b.c_name=n_value WHERE condition`，其中a,b是为两个表起的别名。
3. 删除记录时，可以同时删除多个表中的字段。用法：`DELETE a,b FROM tb_name1 a,tb_name2 b WHERE condition`。
4. 查询记录时，`SELECT`后可加`DISTINCT`去重。后加`ORDER BY c_name DESC/ASC,...`实现排序，ASC默认升序，DESC降序。后加`LIMIT start,count`只输出start开始前count个,start默认为0
5. **外连接** 分为左连接和右连接。 **左连接**：包含所有的左边表中的记录甚至是右边表中没有和它匹配的记录。 **右连接**：包含所有的右边表中的记录甚至是左边表中没有和它匹配的记录。用法`SELECT c1_name,c2_name FROM tb1_name LEFT/RIGHT JOIN tb2_name ON condition`
6. `SELECT`也可用在`condition`条件中，称为 **子查询**。`SELECT...WHERE (..SELECT(...))`
7. `HAVING`和`WHERE`的区别：前者时对聚合后的结果进行条件的过滤，而后者是在聚合前就对记录进行过滤。

### 3、DCL语句
* DCL（Data   Control    Language）语句：数据控制语句，用于控制不同数据段直接的许可和访问级别的语句。这些语句定义了数据库、表、  字段  、用户的访问权限和安全级别。主要的语句关键字包括grant、revoke等。
* `GRANT SELECT/INSERT ON db_name.* TO ’user‘@'localhost' INDENTIFIED BY 'password'`。创建数据库用户，具有对某数据库的select/insert权限

### 4、聚合函数

|Syntaxes                | Results|
|----                    |----    |
|SUM(c_name)             | 字段的总和|
|AVG(c_name)             | 字段的平均数|
|MIN(c_name)             | 字段的最小值|
|MAX(c_name)             | 字段的最大值|
|COUNT(c_name/*)         | 字段的个数|

## 二、MySQL支持的数据类型
### 1. 数值类型

|TINYINT|SMALLINT|DEDIUMINT|INT/INTERGER|BIGINT|
|---|---|---|---|---|
|FLOAT|DOUBLE|DEC(M,D)/DECIMAL(M,D)|BIT(M)|

* 整数类型的操作若超出对应范围，则报出"Out of range"错误。后加括号可指定宽度，后加`ZEROFILL`在位数不够时用0填满。
* 定点数decimal(m,d)中，m表示精度(整数位+小数位共保留m位)，d表示标度(保留小数点后d位)
* bit(m)存放二进制数，m制定位数，范围为1-64，默认为1。插入的值超过范围则报出"Data too long"错误。select命令不显示结果，可以用`bin(c_name), hex(c_name)`显示二进制或十六进制的结果。

### 2. 字符串类型

|CHAR(M)|VARCHAR(M)|BINARY(M)|VARBINARY(M)|ENUM(...)|
|---|---|---|---|---|
|m范围0-255|m范围0-65535|m任意|m任意|枚举类型内元素个数、类型任意|

* char和varchar的区别在于，检索时char删除尾部的空格,varchar则保留空格。
* binary和varbinary类型，不足最大长度的空间用'\0'补全.
* enum类型忽略大小写，当插入值不在制定范围内，则插入第一值。

## 三、MySQL中的运算符

1. 算数运算符

|Operator | Results |
|--- | --- |
| + - *         | 加法减法乘法|
| / DIV         | 除法|
| % MOD         | 取模|

2. 比较运算符

|Operator | Results |
|--- | --- |
| < <= = > >=   | 小于 小于等于 等于 大于 大于等于|
| <> !=         | 不等于|
| <=>           | NULL的安全等于|
| BETWEEN a AND b| 存在于指定范围[a, b]|
| IN            | 存在于指定集合|
| IS (NOT) NULL | (不)为NULL|
| LIKE          | 通字符匹配|
| REGEXP / RLIKE| 正则表达式匹配|

3. 逻辑运算符

|Operator | Results |
|--- | --- |
| NOT / !       | 逻辑非|
| AND / &&      | 逻辑与|
| OR / 丨丨       | 逻辑或|
| XOR           | 逻辑异或|

4. 位运算符

|Operator | Results |
|--- | --- |
| &             | 按位与|
| 丨            | 按位或|
| ^             | 按位异或|
| ~             | 按位取反|
| >>            | 右移|
| <<            | 右移|

## 四、视图

* 视图（View）是一种虚拟存在的表，对于使用视图的用户来说基本上是透明的。视图并不在数据库中实际存在，行和列数据来自定义视图的查询中使用的表，并且是在使用视图时动态生成的。一旦基本表中的数据发生变化，从视图中查询的数据页随之改变。

视图相对于表的优势包括以下几项：

1. **简单** ：使用视图的用户完全不需要关心后面对应的表的结构、关联条件和筛选条件，对用户来说已经是过滤好的复合条件的结果集。
2. **安全** ：使用视图的用户只能访问他们被允许查询的结果集，对表的权限管理并不能限制到某个行某个列，但是通过视图就可以简单的实现。
3. **数据独立** ：一旦视图的结构确定了，可以屏蔽表结构变化对用户的影响，源表增加列对视图没有影响；源表修改列名，则可以通过修改视图来解决，不会造成对访问者的影响

|Syntaxes                | Results  |
|----                    | ----     |
|CREATE (OR REPLACE) VIEW v_name (colume_list) AS select_statement | 创建视图|
|ALTER VIEW v_name (c_list) AS select_statement | 修改视图 |
|DROP VIEW (IF EXISTS) v_names..    | 删除视图 |
|SELECT c_list FROM v_name WHERE condition| 查询视图 |


* 创建视图语句后可加`WITH CHECK OPTION`子句，则以后对该视图进行插入、修改和删除操作时，关系数据库管理系统会自动加上子查询的条件，以确保视图一致性，以保证视图中的记录都满足子查询的where条件。with后可加`CASCADED/LOCAL`，默认cascaded只有满足针对该视图的所有视图的条件才可以更新，后者只要满足本视图的条件就可以更新。
* 创建视图时from关键字后不能加子查询，可以先将子查询定义为一个视图，再对该视图再创建视图就能试下类似的功能了。查看视图`show tables`命令不仅显示表名，也显示视图名。

## 五、存储过程和函数
* **存储过程** 和 **函数** 是事先经过编译并存储在数据库中的一段SQL语句的集合，调用存储过程和函数可以减少数据在数据库和应用服务器之间的传输，提高数据处理的效率。**二者的区别** 在于函数必须有返回值，而存储过程没有，存储过程的参数可以使用IN、OUT、INOUT类型，而函数的参数只能是IN类型的。如果有函数从其他类型的数据库迁移到MySQL，那么就可能因此需要将函数改造成存储过程。

|Syntaxes               |Results            |
|----|----|
|DROP PROCEDURE / FUNCTION (IF EXISTS) sp_name | (若存在则) 删除 存储过程/函数|
|SHOW PROCEDURE / FUNCTION STATUS (LIKE '...') | 查询存储过程/函数的状态|
|SHOW CREATE PROCEDURE / FUNCTION sp_name      | 查看存储过程/函数的定义|
|CALL sp_name(p_name...);                      | 调用存储过程/函数|
|DECLAR var_name... type (DEFAULT value)       | 定义变量, 必须卸载begin-end块中, 写在其他语句前面|
|SET var_name = value...                       | 对变量进行赋值|
|SELECT value... INTO var_name... (from t_name where condition)| 通过查询将结果赋值给变量|




```mysql
DELIMITER $$            # 指定mysql解释器命令行结束符, 默认为 ';'

# 定义存储过程
CREATE PROCEDURE sp_name (IN/OUT/INOUT p_name p_type...)
  # characteristics:
  DETERMINISTIC / NOT DETERMINISTIC  # deterministic 保证对同一输入参数产生同一结果, 默认为后者
  READS SQL DATA        # 对数据库只读, 不能修改
  MODIFY SQL DATA       # 对数据库可以读取, 修改, 删除
  NO SQL                # 程序不包含sql语句
  CONTAINS SQL          # 默认为 contains sql, 包含 sql 语句, 但不对数据库进行读取或写入
  BEGIN
    (...)
  END $$

# 定义函数
CREATE FUNCTION f_name (IN/OUT/INOUT p_name p_type...)
  RETURNS type
  (characteristics...)
  BEGIN
    (...)
    RETURN variable;
  END $$

DELIMITER ;             # 将结束符改回 ';'
```

* **流程控制**：可以使用IF, CASE, LOOP, LEAVE, ITERATE, REPEAT及WHILE语句进行流程的控制, 用法如下:

```mysql
# if 语句
  IF case THEN statement;
    ELSEIF case THEN statement;
    ELSE statement;
  END IF;

# case 语句
  CASE (v_name)         # 若无 v_name 则 when 后为判断条件
    WHEN value THEN statement;
    ELSE statement;
  END CASE;

# LOOP-LEAVE-ITERATE 语句
  label_name: LOOP      # leave跳出循环, iterate进入下一轮循环
   (statement)
   IF condition THEN LEAVE/ITERATE  label_name;
    END IF;
  END LOOP label_name;

# REPEAT-UNTIL 语句
  (label_name:) REPEAT
    (statement)
  UNTIL condition END REPEAT (label_name);

# WHILE-DO 语句
  (label_name:) WHILE CONDITION DO
    (statement)
  END WHILE (label_name);
```






