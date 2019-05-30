<%--
  Created by IntelliJ IDEA.
  User: Joy
  Date: 5/30/2019
  Time: 6:46 PM
  To change this template use File | Settings | File Templates.
--%>
<%@page import="com.sun.org.apache.xpath.internal.functions.Function"%>
<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%@ page import="com.opensymphony.xwork2.ActionContext" %>
<%@ page import="org.hibernate.Session" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
    <title>学生登陆成功！</title>

    <meta http-equiv="pragma" content="no-cache">
    <meta http-equiv="cache-control" content="no-cache">
    <meta http-equiv="expires" content="0">
    <meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
    <meta http-equiv="description" content="This is my page">
    <link rel="stylesheet" href="css.css"/>
    <title>常州大学教务系统</title>
</head>
<body>
<%
    Map _233 = ActionContext.getContext().getSession();
    String account = (String) _233.get("studentId");
%>

<div class="above">
    <center>
        <img src="image/logo.PNG" width="1154px" height="184px">
    </center>
</div>
<div class="middle">
    <div class="middle1">
        <div class="middle1-left">
            <div class="middle-left-1">
                <img src="image/2.PNG" width="270px" height="83px">
            </div>
            <div class="middle1_1">
            </div>
            <div  class="middle1_1">
                <a href="index.jsp">注销登陆 |</a>
            </div>
            <div  class="middle1_2">
                <img src="image/4.PNG" width="270px" height="375px">
            </div>
        </div>
        <div class="middle1-right">
            <div class="middle2_1">
                <p style="color:green;font-size: 22px">&nbsp;&nbsp;&nbsp;登陆成功</p>
                <p style="color:green;font-size:15px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;您(学工号：<%=account%>)已经成功登录教务单点登录接入平台,可以开始使用以下应用系统，祝您使用愉快！</p>
                <br>
                <hr style="border: dashed 0.5px grey;width:96%">
                <br>
                <p style="color:grey;font-size: 15px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;TIPS：出于安全考虑，当您离开应用系统时，请点击注销按钮，并在操作完成之后关闭浏览器。</p>
                <br><br>

                <input name="submit" type="button" value="进入选课系统" onclick="window.location.href='selectCourse.jsp'"/>
                <input name="submit" type="button" value="查询当前课表" onclick="window.location.href='showTable.jsp'"/>
            </div>
        </div>
    </div>
</div>
<div class="bottom">
    <p style="color:grey;font-size: 15px;text-align:center">
        Copyright © 2011常州大学教务处All rights reserved.<br>
        地 址：江苏省常州市科教城常州大学文正楼邮编：213164<br>
        Visual Designer：KingJoy
    </p>
</div>

</body>
</html>