package SQLSyntax;

public class seller implements SQLSyntax {  //对卖家表增删改查

    private static final String now = "CommercialHouse.seller";

    public String insert(String... data) {   //sellerId, password, name
        return "insert into " + now + " values ('" + data[0] + "', '" + data[1] + "', '" + data[2] + "')";
    }

    public String delete(String... data) {   //sellerId
        return "delete from " + now + " where sellerId = '" + data[0] + "'";
    }

    public String modify(String... data) {  //sellerId, newPassword, newName
        return "update " + now + " set password = '" + data[1] + "', name = '" + data[2]
                + "' where sellerId = '" + data[0] + "'";
    }

    public String query(String... data) {   //sellerId
        return "select * from " + now + " where sellerId = '" + data[0] + "'";
    }
}
