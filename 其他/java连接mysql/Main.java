public class Main {

    public static void main(String[] args) {

        final String schema = "_233";
        //��ѯ"��Ϣϵ"ѧ����ѧ�ţ������ͳ������
        final String query = "select sno, sname, 2018 - sage sbirth from student where sdept = '��Ϣϵ'";

//        final String query = "select * from test";
        final String insert = "insert into test values ('����')";
        final String delete = "delete from test where t = 'Hello'";

        MYSQL test = new MYSQL(schema);
        test.query(query, 3);   //��ָ������
        test.update(insert);
        test.update(delete);

        test.CLOSE();
    }

}
