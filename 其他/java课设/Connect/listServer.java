package Connect;

import SQLSyntax.*;

import java.util.ArrayList;

public class listServer implements JDBCServer {

    public boolean insert(String... data) {   //orderId, buyerId, buildingId, roomId, date
        if (data.length != 5) return false;
        return JDBC.SQLexcute(new order().insert(data));
    }

    public boolean delete(String... data) {   //orderId, buyerId, buildingId, roomId
        if (data.length != 4) return false;
        return JDBC.SQLexcute(new order().delete(data));
    }

    public boolean modify(String... data) {  //orderId, buyerId, buildingId, roomId, newDate
        return false;    //非主键属性date在创建时生成，不进行修改
    }

    public ArrayList<String> query(String... data) {   //orderId, buyerId, buildingId, roomId

        if (data.length != 4) return null;
        return JDBC.SQLQuery(new order().query(data));
    }
}
