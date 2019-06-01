<%@ page import="com.opensymphony.xwork2.ActionContext" %>
<%@ page import="java.util.Map" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="Table.realTable" %><%--
  Created by IntelliJ IDEA.
  User: Joy
  Date: 6/1/2019
  Time: 9:17 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>当前的课表</title>

    <meta http-equiv="pragma" content="no-cache">
    <meta http-equiv="cache-control" content="no-cache">
    <meta http-equiv="expires" content="0">
    <meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
    <meta http-equiv="description" content="This is my page">
    <link rel="stylesheet" href="css.css"/>
    <title>常州大学教务系统</title>
</head>
<body>

<div class="above">
    <div style="text-align: center;">
        <img src="image/logo.PNG" width="1154" height="184">
    </div>
</div>

<%
    Map _233 = ActionContext.getContext().getSession();
    String account = (String) _233.get("studentId");
    ArrayList<ArrayList<String>> res = (ArrayList<ArrayList<String>>) _233.get("table");
//    ArrayList<realTable> res = (ArrayList<realTable>) _233.get("table");
%>

<p style="color:green;font-size:15px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;您(学工号：<%=account%>)的当前课表：</p>
<br>
<br>

<div class="middle">
    <div class="middle1">
        <div style="text-align: center;">
            <br>
            <div class="c1"> 显示查询结果</div>

            <table border="2">
                <tr>
                    <th>周一</th>
                    <th>周二</th>
                    <th>周三</th>
                    <th>周四</th>
                    <th>周五</th>
                    <th>周六</th>
                    <th>周日</th>
                </tr>
                <%
                    for (int i = 0; i < res.size(); i++) {
                %>
                <tr>
                    <%
                        for (int j = 0; j < res.get(i).size(); j++) {
                    %>
                    <td><%=res.get(i).get(j)%>
                    </td>
                    <%
                        }
                    %>
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