package SQLSyntax;

public class room implements SQLSyntax {    //对商品房表增删改查

    private static final String now = "CommercialHouse.room";
    public String insert(String... data) {   //roomId, buildingId, category, cost
        return "insert into " + now + " values ('" + data[0] + "', '" +
                data[1] + "', '" + data[2] + "', '" + data[3] + "')";
    }

    public String delete(String... data) {   //roomId, buildingId
        return "delete from " + now + " where (roomId = '" + data[0] + "' and buildingId = '" + data[1] + "')";
    }

    public String modify(String... data) {  //roomId, buildingId, newCategory, newCost
        return "update " + now + " set category = '" + data[2] + "', cost = '" + data[3] +
                "' where (roomId = '" + data[0] + "' and buildingId = '" + data[1] + "')";
    }

    public String query(String... data) {   //roomId, buildingId
        return "select * from " + now + " where (roomId = '" + data[0] + "' and buildingId = '" + data[1] + "')";
    }

    public String modifyCategory(String roomId, String buildingId, boolean Category) {
        return "update " + now + " set category = '" + String.valueOf(Category) +
                "' where (roomId = '" + roomId + "' and buildingId = '" + buildingId + "')";
    }

    public String modifyCost(String roomId, String buildingId, double cost) {
        return "update " + now + " set cost = '" + String.valueOf(cost) +
                "' where (roomId = '" + roomId + "' and buildingId = '" + buildingId + "')";
    }
}
