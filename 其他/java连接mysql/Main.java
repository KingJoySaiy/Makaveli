public class Main {

    public static void main(String[] args) {

        final String schema = "_233";
        final String query = "select * from test";
        final String insert = "insert into test values ('°¡¹þ')";
        final String delete = "delete from test where t = '°¡¹þ'";

        MYSQL test = new MYSQL(schema);
        test.query(query, 1);
        test.update(insert);
        test.query(query, 1);
        test.update(delete);

        test.CLOSE();
    }

}
