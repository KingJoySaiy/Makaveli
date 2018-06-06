import java.sql.*;

public class JDBC {

    private static String schema;
    private static final String NAME = "root";          //登录名
    private static final String PASSWORD = "神秘代码";   //密码
    private static final String DRIVER = "com.mysql.jdbc.Driver";
    private Connection conn = null;

    public JDBC(String c_name) {                   //连接数据库

        use_schema(c_name);
    }
    public void use_schema(String c_name) {         //更改连接的数据库

        schema = c_name;
        String URL = "jdbc:mysql://localhost:3306/" + schema + "?useUnicode=true&characterEncoding=GBK";
        try {
            if(conn != null) CLOSE();
            Class.forName(DRIVER);                  //加载驱动程序
            conn = DriverManager.getConnection(URL, NAME, PASSWORD);    //获取连接
            System.out.println(schema + "数据库连接成功！");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    public void CLOSE() {   //关闭数据库
        try {
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
            conn = null;
        }
    }
    public void query(String que, int column_num) {     //调用查询语句

        try {
            Statement statement = conn.createStatement();
            ResultSet result = statement.executeQuery(que);
            System.out.println("查询结果为：");

            while(result.next()) {
                for(int i = 1; i <= column_num; i++)
                    System.out.print(result.getString(i) + " ");
                System.out.println();
            }
        } catch (SQLException e) {
            e.printStackTrace();    //异常信息在程序中出错的位置和信息
        }
    }
    public void update(String sql) {

        try {
            PreparedStatement p_Statement = conn.prepareStatement(sql);
            p_Statement.executeUpdate();
            System.out.println("执行成功!");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}