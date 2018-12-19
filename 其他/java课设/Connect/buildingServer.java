package Connect;

import SQLSyntax.building;

import java.sql.SQLException;
import java.util.ArrayList;

public class buildingServer implements JDBCServer {

    public boolean insert(String... data) {   //buildingId, buildingName, sellerId, location, count
        if (data.length != 5) return false;
        boolean ok = true;
        try {
            if (!JDBC.SQLexcute(new building().insert(data))) ok = false;
            if (!new roomServer().insertAll(data[0], Math.random() > 0.5, Integer.valueOf(data[4]))) ok = false;
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            return ok;
        }
    }

    public boolean delete(String... data) {   //buildingId, sellerId
        if (data.length != 2) return false;
        return JDBC.SQLexcute(new building().delete(data));
    }

    public boolean modify(String... data) {  //buildingId, sellerId, newBuildingName, newLocation, newCount
        if (data.length != 5) return false;
        return JDBC.SQLexcute(new building().modify(data));
    }

    public ArrayList<String> query(String... data) throws SQLException {   //buildingId, sellerId
        if (data.length != 2) return null;
        return JDBC.SQLQuery(new building().query(data));
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
