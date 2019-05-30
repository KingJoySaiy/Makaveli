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

<div class="above">
    <div style="text-align: center;">
        <img src="image/logo.PNG" width="1154" height="184">
    </div>
</div>
<div class="middle">
    <div style="text-align: center">
        <h2>欢迎使用课程查询系统!</h2>
        <hr>
        <form action="queryCourseByWord.action" method="post">
            请输入查询课程关键字：<input type="text" name="Word"><br><br>
            <input type="submit" value="查询">
        </form>
    </div>
</div>


<div class="bottom">
    <p style="color:grey;font-size: 15px;text-align:center">
        Copyright © 2011常州大学教务处All rights reserved.<br>
        地 址：江苏省常州市科教城常州大学文正楼邮编：213164<br>
        Visual Designer：KingJoySaiy
    </p>
</div>

</body>
</html>