<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
    <title>学生登录</title>

    <meta http-equiv="pragma" content="no-cache">
    <meta http-equiv="cache-control" content="no-cache">
    <meta http-equiv="expires" content="0">
    <meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
    <meta http-equiv="description" content="This is my page">
    <link rel="stylesheet" type="text/css" href="css0.css"/>

</head>
<body>

<div class="a1">
    <div class="b1">
        <div class="c1"><img src="${pageContext.request.contextPath}/image0/p2.png" align="left"/></div>
        <div class="c2"><img src="${pageContext.request.contextPath}/image0/p3(1).png" align="left"/></div>
        <div class="js0">
            在线选课系统登录接入平台
        </div>
    </div>
</div>
<div class="a2">
    <div class="c3"><img src="${pageContext.request.contextPath}/image0/p1.jpg" align="left"/></div>
    <div class="b2">
        <%--<div class="d1">--%>
            <%--账号:<br><br>--%>
            <%--密码：--%>
        <%--</div>--%>
        <div class="d2">
            <form action="loginStudent.action" method="post">
                <input class="t1" type="text" name="sId" value="这里输入学号"/><br><br>
                <input class="t1" type="text" name="password" value="这里输入密码"/><br><br><br>
                <input class="t2" type="submit" name="submit" value="登录"/>
            </form>
            <%--<form name="loginform"><input class="t2" type="submit" value="重置" onclick="login()"/></form>--%>
        </div>
        <div class="d3">
            <br>
            <ul class="js1">
                <li>注意事项：<br/>
                    1.用户名是学号（学生）初始密码为身份证后6位，字母为大写，请登陆后及时修改初始密码。<br/>
                    2.由于安全考虑，一旦您访问过那些需要您提供认证信息的应用时，请操作完成后关闭浏览器。<br/>
                </li>
            </ul>
        </div>

    </div>
</div>
<div class="a3"></div>
</body>
</html>
