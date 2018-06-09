import java.sql.*;
import java.util.Vector;

public class JDBC {

    private static final String sql_url = "jdbc:mysql://localhost:3306/school?useUnicode=true&characterEncoding=GBK";	//数据库路径（一般都是这样写），test是数据库名称
    private static final String name = "root";		//用户名
    private static final String password = "root";	//密码
    private static Connection conn = null;
    private static PreparedStatement preparedStatement = null;
    private static final String all = "select * from student";
    private static final String part = "select sno, sname, 2018 - SAGE from student where SDEPT = '信息系'";

    public static Connection GetConn() {       //获取Connection接口

        try {
            Class.forName("com.mysql.jdbc.Driver");     //加载驱动
            conn = DriverManager.getConnection(sql_url, name, password);       //连接数据库
        } catch (Exception e) {
            e.printStackTrace();
        }
        return conn;
    }
    public static Vector getRows(boolean choose) {  //获取表数据, choose true整个表, false信息系

        Vector rows = null;
        try {
            conn = GetConn();
            String tmp = choose ? "select * from student" :
                    "select sno, sname, 2018 - SAGE from student where SDEPT = '信息系'";
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

    public static Vector getHead() {            //获取表头

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

    // 得到数据库中下一行数据
    private static Vector getNextRow(ResultSet rs, ResultSetMetaData rsmd) throws SQLException {

        Vector currentRow = new Vector();
        for(int i = 1; i <= rsmd.getColumnCount(); i++){
            currentRow.addElement(rs.getString(i));
        }
        return currentRow;
    }
}
