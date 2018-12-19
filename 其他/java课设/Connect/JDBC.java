package Connect;

import java.sql.*;
import java.util.*;

public class JDBC {

    private static final String sql_url = "jdbc:mysql://localhost:3306/CommercialHouse?" +
            "useUnicode=true&useJDBCCompliantTimezoneShift=true" +
            "&useLegacyDatetimeCode=false&serverTimezone=UTC" +
            "&characterEncoding=utf-8";    //数据库路径
    private static final String name = "root";        //用户名
    private static final String password = "233";    //密码
    private static Connection conn = null;
    private static PreparedStatement preparedStatement = null;

    private static Connection GetConn() {       //获取Connection接口

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");     //加载驱动
            conn = DriverManager.getConnection(sql_url, name, password);       //连接数据库
        } catch (Exception e) {
            e.printStackTrace();
        }
        return conn;
    }

    private static ArrayList<String> getNextRow(ResultSet rs, ResultSetMetaData now) throws SQLException {// 得到数据库中下一行数据

        ArrayList<String> currentRow = new ArrayList<>();
        for (int i = 1; i <= now.getColumnCount(); i++) {   //添加所有列属性
            currentRow.add(rs.getString(i));
        }
        return currentRow;
    }

    public static boolean SQLexcute(String sql) {   //执行增删改语句

        int ok = 0;
        try {
            conn = GetConn();
            preparedStatement = conn.prepareStatement(sql);
            ok = preparedStatement.executeUpdate();     //返回值>0则执行成功
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return ok > 0;
    }

    public static ArrayList<String> SQLQuery(String sql) throws SQLException {  //执行按主键查询语句

        ArrayList<String> res = null;
        conn = GetConn();
        preparedStatement = conn.prepareStatement(sql);
        ResultSet result1 = preparedStatement.executeQuery();
        ResultSetMetaData rsmd = result1.getMetaData();
        if (result1.next()) res = getNextRow(result1, rsmd);
        conn.close();
        return res;
    }

    public static ArrayList<ArrayList> getTable(String table, boolean isSQL) throws SQLException {  //获取表数据，返回二维表向量

        if(!isSQL) table = "select * from " + table;
        conn = GetConn();
        preparedStatement = conn.prepareStatement(table);
        ResultSet result1 = preparedStatement.executeQuery();

        ArrayList<ArrayList> rows = new ArrayList<>();
        ResultSetMetaData rsmd = result1.getMetaData();
        while (result1.next()) {
            rows.add(getNextRow(result1, rsmd));
        }
        conn.close();
        return rows;
    }
}