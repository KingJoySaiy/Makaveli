package SQLSyntax;

public class building implements SQLSyntax { //对楼盘表增删改查

    private static final String now = "CommercialHouse.building";

    public String insert(String... data) {   //buildingId, buildingName, sellerId, location, count
        return "insert into " + now + " values ('" + data[0] + "', '" + data[2] + "', '"
                + data[1] + "', '" + data[3] + "', '" + data[4] + "')";
    }

    public String delete(String... data) {   //buildingId, sellerId
        return "delete from " + now + " where (buildingId = '" + data[0] + "' and sellerId = '" + data[1] + "')";
    }

    public String modify(String... data) {  //buildingId, sellerId, newBuildingName, newLocation, newCount
        return "update " + now + " set buildingName = " + data[2] + ", location = '" + data[3] + "', count = '" + data[4] +
                "' where (buildingId = '" + data[0] + "' and sellerId = '" + data[1] + "')";
    }

    public String query(String... data) {   //buildingId, sellerId
        return "select * from " + now + " where (buildingId = '" + data[0] + "' and sellerId = '" + data[1] + "')";
    }

    public String insertDefault(String buildingId, String buildingName, String sellerId, String location) {   //默认插入（套房数量100）
        return "insert into " + now + " values ('" + buildingId + "', '" + sellerId + "', '" + buildingName + "', '" + location + "')";
    }

    public String modifyCount(String buildingId, int newCount) {    //只修改该楼盘剩余房数，传入-1表示减一
        String Count = (newCount == -1 ? "count - 1" : String.valueOf(newCount));
        return "update " + now + " set count = " + Count + " where buildingId = '" + buildingId + "'";
    }

    public String modifyLocation(String buildingId, String newLocation) { //只修改位置
        return "update " + now + " set location = '" + newLocation + "' where buildingId = '" + buildingId + "'";
    }

    public String modifyName(String buildingId, String newName) {  //只修改楼盘名
        return "update " + now + " set buildingName = '" + newName +
                "' where buildingId = '" + buildingId + "'";
    }
}
