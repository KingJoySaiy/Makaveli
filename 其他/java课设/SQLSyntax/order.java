package SQLSyntax;

public class order implements SQLSyntax {  //对订单表增删改查

    private static final String now = "CommercialHouse.list";
    public String insert(String... data) {   //orderId, buyerId, buildingId, roomId, date
        return "insert into " + now + " values ('" + data[0] + "', '" + data[1]
                + "', '" + data[2] + "', '" + data[3] + "', '" + data[4] + "')";
    }

    public String delete(String... data) {   //orderId, buyerId, buildingId, roomId
        return "delete from " + now + " where (orderId = '" + data[0] + "' and buyerId = '" +
                data[1] + "' and buildingId = '" + data[2] + "' and roomId = '" + data[3] + "')";
    }

    public String modify(String... data) {  //orderId, buyerId, buildingId, roomId, newDate
        return null;    //非主键属性date在创建时生成，不进行修改
    }

    public String query(String... data) {   //orderId, buyerId, buildingId, roomId

        return "select * from " + now + " where (orderId = '" + data[0] + "' and buyerId = '" +
                data[1] + "' and buildingId = '" + data[2] + "' and roomId = '" + data[3] + "')";
    }

    public String queryOrderId(String orderId) {

        return "select * form " + now + " where orderId = " + orderId;
    }
}
