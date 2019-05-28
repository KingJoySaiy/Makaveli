<%--
  Created by IntelliJ IDEA.
  User: Joy
  Date: 5/29/2019
  Time: 12:33 AM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>queryBook</title>
</head>
<body>
<h2>欢迎使用课程查询系统!</h2><hr>
<form action="queryCourseByWord.action" method="post">
    请输入查询课程关键字：<input type="text" name="Word"><br><br>
    <input type="submit" value="查询">
</form>
</body>
</html>