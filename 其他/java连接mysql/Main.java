public class Main {

    public static void main(String[] args) {

        final String schema = "_233";
        final String query = "select * from test";
        final String insert = "insert into test values ('����')";
        final String delete = "delete from test where t = '����'";

        MYSQL test = new MYSQL(schema);
        test.query(query, 1);
        test.update(insert);
        test.query(query, 1);
        test.update(delete);

        test.CLOSE();
    }

}
