import SQLSyntax.*;
import Connect.*;

import javax.swing.text.html.HTMLDocument;
import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;

public class Main {

    public static void main(String[] args) throws Exception {

//        sellerServer seller = new sellerServer();
//        seller.delete("joy1");
//        seller.modify("ligan1", "233", "淦李");
//        seller.insert("joy1","123456789","薛金强1");
//        seller.insert("ligan1","123456789","李淦1");
//        seller.insert("ligan2","123456789","李淦2");
//        seller.insert("joy2","123456789","薛金强2");
//        seller.insert("joy3","123456789","薛金强3");
        
//        buildingServer building = new buildingServer();
//        building.delete("1001", "ligan1");
//        building.modify("1003", "ligan1", "location", "100", "常州");
//        building.insert("1001","府居天下","ligan1","100","北京");
//        building.insert("1002","花园别墅","ligan1","110","深圳");
//        building.insert("1003","东方府居","ligan1","50","上海");
//        building.insert("1004","临江首府","ligan1","30","常州");

//        buyerServer buyer = new buyerServer();//buyerId, id, name, phone, password
//        buyer.delete("007");
//        buyer.modify("008", "123456789012345677", "Jason", "12345678902", "233");
//        buyer.insert("007", "123456789012345678", "Joy", "12345678901", "233");
//        buyer.insert("008", "123456789012345677", "Jason", "12345678902", "133");
//        buyer.insert("009", "123456789012345676", "Smith", "12345678900", "abc");
//        buyer.insert("010", "123456789012345675", "Kid", "12345678908", "xyz233");
//        buyer.insert("011", "123456789012345699", "asf", "12345678909", "asd");

//        roomServer room = new roomServer();
//        room.delete("0310", "1003");
//        room.modify("0309", "1003", "二手房", "233");
//        room.insertAll("1003", Math.random() > 0.5, 30);
//        room.insert("001", "1001", "二手房", "100");

        listServer list = new listServer(); //orderId, buyerId, buildingId, roomId
//        list.insert("listId", "007", "1003", "0101");
//        list.deleteList("listId");
//        ArrayList<String> data = list.queryList("listId");
//        for (String p : data) {
//            System.out.println(p);
//        }

        ArrayList<ArrayList> datas = list.queryAll();
        for (ArrayList p : datas) {
            for (Iterator o = p.iterator(); o.hasNext(); ) {
                System.out.print(o.next() + " ");
            }
            System.out.println();
        }


    }
}
