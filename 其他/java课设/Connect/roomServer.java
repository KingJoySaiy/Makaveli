package Connect;

import SQLSyntax.*;

import java.sql.SQLException;
import java.util.ArrayList;

public class roomServer implements JDBCServer {

    public boolean insert(String... data) {   //roomId, buildingId, category, cost
        if (data.length != 4) return false;
        return JDBC.SQLexcute(new room().insert(data));
    }

    public boolean delete(String... data) {   //roomId, buildingId
        if (data.length != 2) return false;
        return JDBC.SQLexcute(new room().delete(data));
    }

    public boolean modify(String... data) {  //roomId, buildingId, newCategory, newCost
        if (data.length != 4) return false;
        return JDBC.SQLexcute(new room().modify(data));
    }

    public ArrayList<String> query(String... data) throws SQLException {   //roomId, buildingId

        if (data.length != 2) return null;
        return JDBC.SQLQuery(new room().query(data));
    }

    public boolean insertAll(String buildingId, boolean catogory, int count) throws SQLException {

        for (int i = 1; i <= count; i++) {
            if(!insert(String.format("%02d", (i - 1) / 10 + 1) + String.format("%02d", (i - 1) % 10 + 1),
                    buildingId, catogory ? "新房" : "二手房", String.valueOf((int)(100 * (Math.random() * 9 + 1)))))
                return false;
        }
        return true;
    }

    public boolean modifyCategory(String roomId, String buildingId, boolean Category) {
        return JDBC.SQLexcute(new room().modifyCategory(roomId, buildingId, Category));
    }

    public boolean modifyCost(String roomId, String buildingId, double cost) {
        return JDBC.SQLexcute(new room().modifyCost(roomId, buildingId, cost));
    }
}
