<%--
  Created by IntelliJ IDEA.
  User: Joy
  Date: 5/29/2019
  Time: 12:43 AM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>My JSP 'make.jsp' starting page</title>

    <meta http-equiv="pragma" content="no-cache">
    <meta http-equiv="cache-control" content="no-cache">
    <meta http-equiv="expires" content="0">
    <meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
    <meta http-equiv="description" content="This is my page">

    <link rel="stylesheet" href="css1.css"/>
    <title>常州大学教务系统</title>
</head>
<body>
<div class="above">
    <div style="text-align: center;">
        <img src="image/logo.PNG" width="1154px" height="184px">
    </div>
</div>
<div class="middle">
    <div class="middle1">
        <div style="text-align: center;">
            <form action="addCourse.action" method="post">
                请输入课程相关属性：<br>
                课 程 号: <input class="middle3" type="text" name="cId" value=""/><br>
                课 程 名: <input class="middle3" type="text" name="cName" value=""/><br>
                教师名: <input class="middle3" type="text" name="teacher" value=""/><br>
                <input class="middle4" type="submit" name="submit" value="确定"/>
            </form>
        </div>
    </div>
</div>
<div class="bottom">
    <p style="color:grey;font-size: 15px;text-align:center">
        Copyright © 2011常州大学教务处All rights reserved.<br>
        地 址：江苏省常州市科教城常州大学文正楼邮编：213164<br>
        Visual Designer：艺术系廖丰丰
    </p>
</div>
<body>