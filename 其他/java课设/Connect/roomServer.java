package Connect;

import SQLSyntax.*;

import java.util.ArrayList;

public class roomServer implements JDBCServer {

    public boolean insert(String... data) {   //roomId, buildingId, category, cost
        if (data.length != 4) return false;
        return JDBC.SQLexcute(new room().insert(data));
    }

    public boolean delete(String... data) {   //roomId, buildingId
        if (data.length != 2) return false;
        return JDBC.SQLexcute(new room().insert(data));
    }

    public boolean modify(String... data) {  //roomId, buildingId, newCategory, newCost
        if (data.length != 4) return false;
        return JDBC.SQLexcute(new room().insert(data));
    }

    public ArrayList<String> query(String... data) {   //roomId, buildingId

        if (data.length != 2) return null;
        return JDBC.SQLQuery(new room().query(data));
    }

    public boolean modifyCategory(String roomId, String buildingId, boolean Category) {
        return JDBC.SQLexcute(new room().modifyCategory(roomId, buildingId, Category));
    }

    public boolean modifyCost(String roomId, String buildingId, double cost) {
        return JDBC.SQLexcute(new room().modifyCost(roomId, buildingId, cost));
    }
}
