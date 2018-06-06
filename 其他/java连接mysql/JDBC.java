import java.sql.*;

public class JDBC {

    private static String schema;
    private static final String NAME = "root";          //��¼��
    private static final String PASSWORD = "���ش���";   //����
    private static final String DRIVER = "com.mysql.jdbc.Driver";
    private Connection conn = null;

    public JDBC(String c_name) {                   //�������ݿ�

        use_schema(c_name);
    }
    public void use_schema(String c_name) {         //�������ӵ����ݿ�

        schema = c_name;
        String URL = "jdbc:mysql://localhost:3306/" + schema + "?useUnicode=true&characterEncoding=GBK";
        try {
            if(conn != null) CLOSE();
            Class.forName(DRIVER);                  //������������
            conn = DriverManager.getConnection(URL, NAME, PASSWORD);    //��ȡ����
            System.out.println(schema + "���ݿ����ӳɹ���");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    public void CLOSE() {   //�ر����ݿ�
        try {
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
            conn = null;
        }
    }
    public void query(String que, int column_num) {     //���ò�ѯ���

        try {
            Statement statement = conn.createStatement();
            ResultSet result = statement.executeQuery(que);
            System.out.println("��ѯ���Ϊ��");

            while(result.next()) {
                for(int i = 1; i <= column_num; i++)
                    System.out.print(result.getString(i) + " ");
                System.out.println();
            }
        } catch (SQLException e) {
            e.printStackTrace();    //�쳣��Ϣ�ڳ����г����λ�ú���Ϣ
        }
    }
    public void update(String sql) {

        try {
            PreparedStatement p_Statement = conn.prepareStatement(sql);
            p_Statement.executeUpdate();
            System.out.println("ִ�гɹ�!");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}