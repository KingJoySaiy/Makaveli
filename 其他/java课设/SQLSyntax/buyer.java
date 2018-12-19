package SQLSyntax;

public class buyer implements SQLSyntax {   //对卖家表增删改查

    private static final String now = "CommercialHouse.buyer";
    public String insert(String... data) {   //buyerId, id, name, phone, password
        return "insert into " + now + " values ('" + data[0] + "', '" + data[1] + "', '"
                + data[2] + "', '" + data[3] + "', '" + data[4] + "')";
    }

    public String delete(String... data) {   //buyerId
        return "delete from " + now + " where buyerId = '" + data[0] + "'";
    }

    public String modify(String... data) {  //buyerId, id, name, phone, password
        return "update " + now + " set id = '" + data[1] + "', name = '" + data[2]
            + "', phone = '" + data[3] + "', password = '" + data[4] + "' where buyerId = '" + data[0] + "'";
    }

    public String query(String... data) {   //buyerId
        System.out.println("select * from " + now + " where buyerId = '" + data[0] + "'");
        return "select * from " + now + " where buyerId = '" + data[0] + "'";
    }

    public String modifyPhone(String buyerId, String newPhone) {    //修改手机号

        return "update " + now + " set phone = '" + newPhone +
                "' where phone = '" + buyerId + "'";
    }
    public String modifyPassword(String buyerId, String newPassword) {  //修改密码

        return "update" + now + "set password = '" + newPassword +
                "' where password = '" + newPassword + "'";
    }
}
