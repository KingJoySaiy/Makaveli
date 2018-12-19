package Connect;

import SQLSyntax.*;

import java.sql.SQLException;
import java.util.ArrayList;

public class sellerServer implements JDBCServer {

    public boolean insert(String... data) {   //sellerId, password, name
        if (data.length != 3) return false;
        return JDBC.SQLexcute(new seller().insert(data));
    }

    public boolean delete(String... data) {   //sellerId
        if (data.length != 1) return false;
        return JDBC.SQLexcute(new seller().delete(data));
    }

    public boolean modify(String... data) {  //sellerId, newPassword, newName
        if (data.length != 3) return false;
        return JDBC.SQLexcute(new seller().modify(data));
    }

    public ArrayList<String> query(String... data) throws SQLException {   //sellerId
        if (data.length != 1) return null;
        return JDBC.SQLQuery(new seller().query(data));
    }
}
