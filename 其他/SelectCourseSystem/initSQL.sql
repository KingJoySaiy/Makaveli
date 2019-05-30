-- 课程（课程号，课程名，教师名）
create table course (
  cid int(6) primary key auto_increment,
  cname varchar(20) not null,
  teacher varchar(20) not null
);

-- 每周安排（课程号，开始周，结束周，星期几1-7，地点，上课时间1-10，课程长度1-3）
create table courseDemo (
  cid int(6) references course(cid),
  sweek int not null default 1 check(sweek between 1 and 20),
  eweek int not null check((eweek between 1 and 20) and (sweek <= eweek)),
  day int check (day between 1 and 7),
  location varchar(20) not null,
  stime int not null check (stime between 1 and 10),
  length int not null default 1 check (length between 1 and 3),
  primary key(cid, day)
);

-- 学生（学号，密码，姓名，班级）
create table student (
  sid varchar(8) primary key,
  password varchar(20) not null,
  name varchar(20) not null,
  sclass varchar(20)
);

-- 选课关系（学号，课程号）
create table selected (
  sid varchar(8) references student(sid),
  cid int(6) references weekly(cid),
  primary key(sid, cid)
);

-- 在线选课系统
-- 包括（1）用户登录、（2）课程信息录入，
-- （3）课程查询（支持模糊查询），
-- （4）选课功能。其中，（1）用户登录每个人都要实现，
-- 另外三个模块每人选做一个。
-- 数据库表格的设计合作完成。