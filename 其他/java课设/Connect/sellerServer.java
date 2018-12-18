package Connect;

import SQLSyntax.*;

import java.util.ArrayList;

public class sellerServer implements JDBCServer {

    public boolean insert(String... data) {   //sellerId, name
        if (data.length != 2) return false;
        return JDBC.SQLexcute(new seller().insert(data));
    }

    public boolean delete(String... data) {   //sellerId
        if (data.length != 1) return false;
        return JDBC.SQLexcute(new seller().delete(data));
    }

    public boolean modify(String... data) {  //sellerId, newName
        if (data.length != 2) return false;
        return JDBC.SQLexcute(new seller().modify(data));
    }

    public ArrayList<String> query(String... data) {   //sellerId
        if (data.length != 1) return null;
        return JDBC.SQLQuery(new seller().query(data));
    }
}
