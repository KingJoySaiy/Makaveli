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
            <form action="addCourseDemo.action" method="post">
                请输入课程具体属性：<br>
                课程号: <input class="middle3" type="text" name="cId" value=""/><br>
                开始周[1-20]: <input class="middle3" type="text" name="sWeek" value=""/><br>
                结束周[1-20]: <input class="middle3" type="text" name="eWeek" value=""/><br>
                星期几[1-7]: <input class="middle3" type="text" name="day" value=""/><br>
                上课地点: <input class="middle3" type="text" name="location" value=""/><br>
                时间[1-10]: <input class="middle3" type="text" name="sTime" value=""/><br>
                连上时间[1-3]: <input class="middle3" type="text" name="length" value=""/><br>
                <input class="middle4" type="submit" name="submit" value="确定"/>
            </form>
        </div>
    </div>
</div>
<div class="bottom">
    <p style="color:grey;font-size: 15px;text-align:center">
        Copyright © 2011常州大学教务处All rights reserved.<br>
        地 址：江苏省常州市科教城常州大学文正楼邮编：213164<br>
        Visual Designer：KingJoySaiy
    </p>
</div>
<body>