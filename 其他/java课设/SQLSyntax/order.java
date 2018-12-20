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

    public String deleteOrderId(String orderId) {   //按照订单号删除

        return "delete from " + now + " where orderId = '" + orderId + "'";
    }

    public String queryOrderId(String orderId) {    //按照订单号查询(listId, buyerId, buildingId, buildingName, location)

        return "select list.listId, buyer.buyerId, building.buildingId, building.buildingName, building.location from list, buyer, building "
                + "where list.buyerId = Buyer.buyerId and list.buildingId = building.buildingId and list.listId = '" + orderId + "'";
    }

    public static String queryAll() {   //查询(listId, sellerId, buyerId, buildingId, buildingName)全部信息

        return "select list.listId, seller.sellerId, buyer.buyerId, building.buildingId, building.buildingName, " +
                "building.location from list, seller, buyer, building where list.buildingId = Building.buildingId " +
                "and list.buyerId = Buyer.buyerId and building.sellerId = seller.sellerId";
    }
}
