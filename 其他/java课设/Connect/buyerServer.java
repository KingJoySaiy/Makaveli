package Connect;

import SQLSyntax.buyer;

import java.sql.SQLException;
import java.util.ArrayList;

public class buyerServer implements JDBCServer {

    public boolean insert(String... data) {  //buyerId, id, name, phone, password
        //身份证18位,手机号11位
        if (data.length != 5 || data[1].length() != 18 || data[3].length() != 11) return false;
        return JDBC.SQLexcute(new buyer().insert(data));
    }

    public boolean delete(String... data) {   //buyerId
        if (data.length != 1) return false;
        return JDBC.SQLexcute(new buyer().delete(data));
    }

    public boolean modify(String... data) {  //buyerId, id, name, phone, password
        if (data.length != 5) return false;
        return JDBC.SQLexcute(new buyer().modify(data));
    }

    public ArrayList<String> query(String... data) throws SQLException {   //buyerId
        if (data.length != 1) return null;
        return JDBC.SQLQuery(new buyer().query(data));
    }

    public boolean modifyPhone(String buyerId, String newPhone) {   //修改手机号

        return JDBC.SQLexcute(new buyer().modifyPhone(buyerId, newPhone));
    }

    public boolean modifyPassword(String buyerId, String newPassword) { //修改密码

        return JDBC.SQLexcute(new buyer().modifyPassword(buyerId, newPassword));
    }
}
