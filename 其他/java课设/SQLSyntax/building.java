package SQLSyntax;

public class building implements SQLSyntax { //对楼盘表增删改查

    private static final String now = "CommercialHouse.building";
    public String insert(String... data) {   //buildingId, sellerId, location, count
        return "insert into " + now + " values ('" + data[0] + "', '" + data[1] + "', '" + data[2] + "', '" + data[3] + "')";
    }

    public String delete(String... data) {   //buildingId, sellerId
        return "delete from " + now + " where (buildingId = '" + data[0] + "' and sellerId = '" + data[1] + "')";
    }

    public String modify(String... data) {  //buildingId, sellerId, newLocation, newCount
        return "update " + now + " set location = '" + data[2] + "', count = '" + data[3] +
                "' where (buildingId = '" + data[0] + "' and sellerId = '" + data[1] + "')";
    }

    public String query(String... data) {   //buildingId, sellerId
        return "select * from " + now + " where (buildingId = '" + data[0] + "' and sellerId = '" + data[1] + "')";
    }

    public String insertDefault(String buildingId, String sellerId, String location) {   //默认插入（套房数量100）
        return "insert into " + now + " values ('" + buildingId + "', '" + sellerId + "', '" + location + "')";
    }

    public String modifyCount(String buildingId, String sellerId, int newCount) {    //只修改该楼盘剩余房数
        return "update " + now + " set count = '" + newCount +
                "' where (buildingId = '" + buildingId + "' and sellerId = '" + sellerId + "')";
    }

    public String modifyLocation(String buildingId, String sellerId, String location) { //只修改位置
        return "update " + now + " set location = '" + location +
                "' where (buildingId = '" + buildingId + "' and sellerId = '" + sellerId + "')";
    }


}
