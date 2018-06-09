import java.sql.*;
import java.util.Vector;

public class JDBC {

    private static final String sql_url = "jdbc:mysql://localhost:3306/school?useUnicode=true&characterEncoding=GBK";	//���ݿ�·����һ�㶼������д����test�����ݿ�����
    private static final String name = "root";		//�û���
    private static final String password = "root";	//����
    private static Connection conn = null;
    private static PreparedStatement preparedStatement = null;
    private static final String all = "select * from student";
    private static final String part = "select sno, sname, 2018 - SAGE from student where SDEPT = '��Ϣϵ'";

    public static Connection GetConn() {       //��ȡConnection�ӿ�

        try {
            Class.forName("com.mysql.jdbc.Driver");     //��������
            conn = DriverManager.getConnection(sql_url, name, password);       //�������ݿ�
        } catch (Exception e) {
            e.printStackTrace();
        }
        return conn;
    }
    public static Vector getRows(boolean choose) {  //��ȡ������, choose true������, false��Ϣϵ

        Vector rows = null;
        try {
            conn = GetConn();
            String tmp = choose ? "select * from student" :
                    "select sno, sname, 2018 - SAGE from student where SDEPT = '��Ϣϵ'";
            preparedStatement = conn.prepareStatement(tmp);
            ResultSet result1 = preparedStatement.executeQuery();

            rows = new Vector();
            ResultSetMetaData rsmd = result1.getMetaData();
            while(result1.next()) {
                rows.addElement(getNextRow(result1,rsmd));
            }
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return rows;
    }

    public static Vector getHead() {            //��ȡ��ͷ

        Vector columnHeads = null;
        try {
            conn = GetConn();
            preparedStatement = conn.prepareStatement("select * from student");
            ResultSet result1 = preparedStatement.executeQuery();

            columnHeads = new Vector();
            ResultSetMetaData rsmd = result1.getMetaData();
            for(int i = 1; i <= rsmd.getColumnCount(); i++)
                columnHeads.addElement(rsmd.getColumnName(i));
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return columnHeads;
    }

    // �õ����ݿ�����һ������
    private static Vector getNextRow(ResultSet rs, ResultSetMetaData rsmd) throws SQLException {

        Vector currentRow = new Vector();
        for(int i = 1; i <= rsmd.getColumnCount(); i++){
            currentRow.addElement(rs.getString(i));
        }
        return currentRow;
    }
}
