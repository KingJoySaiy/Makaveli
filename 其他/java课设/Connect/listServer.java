package Connect;

import SQLSyntax.*;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Date;

public class listServer implements JDBCServer {

    public boolean insert(String... data) {   //listId, buyerId, buildingId, roomId, date
        if (data.length != 4) return false;
        String[] all = new String[data.length + 1];
        for (int i = 0; i < data.length; i++) all[i] = data[i];
        all[data.length] = "(" + new Date().toString() + ")";   //获取当前时间
        return JDBC.SQLexcute(new order().insert(all));
    }

    public boolean delete(String... data) {   //listId, buyerId, buildingId, roomId
        if (data.length != 4) return false;
        return JDBC.SQLexcute(new order().delete(data));
    }

    public boolean deleteList(String listId) {
        return JDBC.SQLexcute("delete from list where listId = '" + listId + "'");
    }

    public boolean modify(String... data) {  //listId, buyerId, buildingId, roomId, newDate
        return false;    //非主键属性date在创建时生成，不进行修改
    }

    public ArrayList<String> query(String... data) throws SQLException {   //listId, buyerId, buildingId, roomId

        if (data.length != 4) return null;
        return JDBC.SQLQuery(new order().query(data));
    }

    public ArrayList<String> queryList(String listId) throws SQLException {

        return JDBC.SQLQuery("select list.listId, buyer.buyerId, building.buildingId, building.buildingName, building.location from list, buyer, building "
                + "where list.buyerId = Buyer.buyerId and list.buildingId = building.buildingId and list.listId = '" + listId + "'");
    }

    public ArrayList<ArrayList> queryAll() throws SQLException {

        return JDBC.getTable("select list.listId, seller.sellerId, buyer.buyerId, building.buildingId, building.buildingName, " +
                "building.location from list, seller, buyer, building where list.buildingId = Building.buildingId " +
                "and list.buyerId = Buyer.buyerId and building.sellerId = seller.sellerId", true);
    }
}
