package Connect;

import SQLSyntax.*;

import java.sql.SQLException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

public class listServer implements JDBCServer {

    public boolean insert(String... data) {   //listId, buyerId, buildingId, roomId, date
        if (data.length != 4) return false;
        String[] all = new String[data.length + 1];
        for (int i = 0; i < data.length; i++) all[i] = data[i];
        all[data.length] = "(" + new SimpleDateFormat("yyyy MM dd hh mm").format(new Date()) + ")";   //获取当前时间
        if (!JDBC.SQLexcute(new building().modifyCount(data[2], -1))) return false;
        return JDBC.SQLexcute(new order().insert(all));
    }

    public boolean delete(String... data) {   //listId, buyerId, buildingId, roomId
        if (data.length != 4) return false;
        return JDBC.SQLexcute(new order().delete(data));
    }

    public boolean deleteList(String orderId) {  //按照订单号删除
        return JDBC.SQLexcute(new order().deleteOrderId(orderId));
    }

    public boolean modify(String... data) {  //listId, buyerId, buildingId, roomId, newDate
        return false;    //非主键属性date在创建时生成，不进行修改
    }

    public ArrayList<String> query(String... data) throws SQLException {   //listId, buyerId, buildingId, roomId

        if (data.length != 4) return null;
        return JDBC.SQLQuery(new order().query(data));
    }

    public ArrayList<String> queryList(String orderId) throws SQLException {    //按照订单号查询(listId, buyerId, buildingId, buildingName, location)

        return JDBC.SQLQuery(new order().queryOrderId(orderId));
    }

    public ArrayList<ArrayList> queryAll() throws SQLException {    //查询(listId, sellerId, buyerId, buildingId, buildingName)全部信息

        return JDBC.getTable(order.queryAll(), true);
    }
}
