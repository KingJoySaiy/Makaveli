import java.sql.*;
import java.util.*;

import javax.swing.JOptionPane;

public class Storage {

    private static final String sql_url = "jdbc:mysql://localhost:3306/_233?useUnicode=true&characterEncoding=GBK";	//���ݿ�·����һ�㶼������д����test�����ݿ�����
    private static final String name = "root";		//�û���
    private static final String password = "root";	//����
    private static final String driver = "com.mysql.jdbc.Driver";
    private static Connection conn = null;
    private static PreparedStatement preparedStatement = null;

    // �õ����ݿ������
    public static Vector getRows() {

        Vector rows = null;

        try {
            Class.forName("com.mysql.jdbc.Driver");		//��������
            conn = DriverManager.getConnection(sql_url, name, password);	//�������ݿ�
            preparedStatement = conn.prepareStatement("select * from student");
            ResultSet result1 = preparedStatement.executeQuery();

            if(result1.wasNull())
                JOptionPane.showMessageDialog(null, "��������޼�¼");

            rows = new Vector();
            ResultSetMetaData rsmd = result1.getMetaData();
            while(result1.next()) {
                rows.addElement(getNextRow(result1,rsmd));
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        return rows;
    }

    // �õ����ݿ��ͷ
    public static Vector getHead() {

        Vector columnHeads = null;
        try {
            Class.forName(driver);		//��������
            conn = DriverManager.getConnection(sql_url, name, password);	//�������ݿ�
            preparedStatement = conn.prepareStatement("select * from student");
            ResultSet result1 = preparedStatement.executeQuery();

            if(!result1.next())
                JOptionPane.showMessageDialog(null, "��������޼�¼");

            columnHeads = new Vector();
            ResultSetMetaData rsmd = result1.getMetaData();
            for(int i = 1; i <= rsmd.getColumnCount(); i++)
                columnHeads.addElement(rsmd.getColumnName(i));

        } catch (Exception e) {
            e.printStackTrace();
        }
        return columnHeads;
    }

    // �õ����ݿ�����һ������
    private static Vector getNextRow(ResultSet rs,ResultSetMetaData rsmd) throws SQLException{
        Vector currentRow = new Vector();
        for(int i = 1; i <= rsmd.getColumnCount(); i++){
            currentRow.addElement(rs.getString(i));
        }
        return currentRow;
    }
}
