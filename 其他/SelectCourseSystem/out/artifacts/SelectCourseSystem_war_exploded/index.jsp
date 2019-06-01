<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
  <title>start</title>
</head>
<body>
  <h2>在线选课系统</h2><hr>
  <table border="2">
    <tr>
      <th></th>
      <th>编号</th>
      <th>功能选择</th>
    </tr>

    <tr>
      <form action="queryCourse.jsp" method="post">
      <td>1</td>
      <td>模糊查询课程</td>
      <td><input type="submit" value="进入"></td>
      </form>
    </tr>

    <tr>
      <form action="addCourse.jsp" method="post">
      <td>2</td>
      <td>添加课程信息</td>
      <td><input type="submit" value="进入"></td>
      </form>
    </tr>

    <tr>
      <form action="addCourseDemo.jsp" method="post">
        <td>3</td>
        <td>添加课程具体信息</td>
        <td><input type="submit" value="进入"></td>
      </form>
    </tr>

    <tr>
      <form action="loginStudent.jsp" method="post">
        <td>4</td>
        <td>学生登录</td>
        <td><input type="submit" value="进入"></td>
      </form>
    </tr>

  </table>
</body>
</html>
