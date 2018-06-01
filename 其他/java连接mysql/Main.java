public class Main {

    public static void main(String[] args) {

        final String schema = "_233";
        //查询"信息系"学生的学号，姓名和出生年份
        final String query = "select sno, sname, 2018 - sage sbirth from student where sdept = '信息系'";

//        final String query = "select * from test";
        final String insert = "insert into test values ('啊哈')";
        final String delete = "delete from test where t = 'Hello'";

        MYSQL test = new MYSQL(schema);
        test.query(query, 3);   //需指定列数
        test.update(insert);
        test.update(delete);

        test.CLOSE();
    }

}
