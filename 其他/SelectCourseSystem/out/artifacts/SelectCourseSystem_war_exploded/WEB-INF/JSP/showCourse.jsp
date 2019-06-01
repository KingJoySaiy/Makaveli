<%@ page import="java.util.ArrayList" %>
<%@ page import="java.util.Map" %>
<%@ page import="com.opensymphony.xwork2.ActionContext" %>
<%@ page import="Table.TCourse" %><%--
  Created by IntelliJ IDEA.
  User: Joy
  Date: 5/29/2019
  Time: 12:18 AM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>当前课程记录</title>

    <meta http-equiv="pragma" content="no-cache">
    <meta http-equiv="cache-control" content="no-cache">
    <meta http-equiv="expires" content="0">
    <meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
    <meta http-equiv="description" content="This is my page">
    <link rel="stylesheet" type="text/css" href="css2.css">


</head>
<body>
<div class="above">
    <div style="text-align: center;">
        <img src="image/logo.PNG" width="1154" height="184">
    </div>
</div>
<div class="middle">
    <div class="middle1">
        <div style="text-align: center;">
            <br>
            <div class="c1"> 显示查询结果</div>

            <table border="2">
                <tr>
                    <th>课程编号</th>
                    <th>课程名称</th>
                    <th>教师</th>
                </tr>
                <%
                    Map se = ActionContext.getContext().getSession();
                    ArrayList<TCourse> courses = (ArrayList<TCourse>) se.get("list");
                    for(int i = 0;i < courses.size();i++) {
                %>
                <tr>
                    <td><%=courses.get(i).getcId()%></td>
                    <td><%=courses.get(i).getcName()%></td>
                    <td><%=courses.get(i).getTeacher()%></td>
                </tr>
                <%
                    }
                %>
            </table>
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
</body>
</html>
