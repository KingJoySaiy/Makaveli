import java.sql.*;
import java.util.*;

import javax.swing.JOptionPane;

public class Storage {

    private static final String sql_url = "jdbc:mysql://localhost:3306/_233?useUnicode=true&characterEncoding=GBK";	//数据库路径（一般都是这样写），test是数据库名称
    private static final String name = "root";		//用户名
    private static final String password = "root";	//密码
    private static final String driver = "com.mysql.jdbc.Driver";
    private static Connection conn = null;
    private static PreparedStatement preparedStatement = null;

    // 得到数据库表数据
    public static Vector getRows() {

        Vector rows = null;

        try {
            Class.forName("com.mysql.jdbc.Driver");		//连接驱动
            conn = DriverManager.getConnection(sql_url, name, password);	//连接数据库
            preparedStatement = conn.prepareStatement("select * from student");
            ResultSet result1 = preparedStatement.executeQuery();

            if(result1.wasNull())
                JOptionPane.showMessageDialog(null, "结果集中无记录");

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

    // 得到数据库表头
    public static Vector getHead() {

        Vector columnHeads = null;
        try {
            Class.forName(driver);		//连接驱动
            conn = DriverManager.getConnection(sql_url, name, password);	//连接数据库
            preparedStatement = conn.prepareStatement("select * from student");
            ResultSet result1 = preparedStatement.executeQuery();

            if(!result1.next())
                JOptionPane.showMessageDialog(null, "结果集中无记录");

            columnHeads = new Vector();
            ResultSetMetaData rsmd = result1.getMetaData();
            for(int i = 1; i <= rsmd.getColumnCount(); i++)
                columnHeads.addElement(rsmd.getColumnName(i));

        } catch (Exception e) {
            e.printStackTrace();
        }
        return columnHeads;
    }

    // 得到数据库中下一行数据
    private static Vector getNextRow(ResultSet rs,ResultSetMetaData rsmd) throws SQLException{
        Vector currentRow = new Vector();
        for(int i = 1; i <= rsmd.getColumnCount(); i++){
            currentRow.addElement(rs.getString(i));
        }
        return currentRow;
    }
}
