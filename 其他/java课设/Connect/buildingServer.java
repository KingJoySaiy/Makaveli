package Connect;

import SQLSyntax.building;

import java.util.ArrayList;

public class buildingServer implements JDBCServer {

    public boolean insert(String... data) {   //buildingId, sellerId, location, count
        if (data.length != 4) return false;
        return JDBC.SQLexcute(new building().insert(data));
    }

    public boolean delete(String... data) {   //buildingId, sellerId
        if (data.length != 2) return false;
        return JDBC.SQLexcute(new building().delete(data));
    }

    public boolean modify(String... data) {  //buildingId, sellerId, newLocation, newCount
        if (data.length != 4) return false;
        return JDBC.SQLexcute(new building().modify(data));
    }

    public ArrayList<String> query(String... data) {   //buildingId, sellerId
        if (data.length != 2) return null;
        return JDBC.SQLQuery(new building().query());
    }

    public boolean insertDefault(String buildingId, String sellerId, String location) {   //默认插入（套房数量100）
        return JDBC.SQLexcute(new building().insertDefault(buildingId, sellerId, location));
    }

    public boolean modifyCount(String buildingId, String sellerId, int newCount) {    //只修改该楼盘剩余房数
        return JDBC.SQLexcute(new building().modifyCount(buildingId, sellerId, newCount));
    }

    public boolean modifyLocation(String buildingId, String sellerId, String location) { //只修改位置
        return JDBC.SQLexcute(new building().modifyLocation(buildingId, sellerId, location));
    }
}
