package Test;

import OperationMode.CTR_RSA;
import OperationMode.RSAMode;

import java.io.*;
import java.math.BigInteger;
import java.util.LinkedList;

public class fileTest {

    public static void fileTest() {

        LinkedList<BigInteger> all = new LinkedList<>();
        LinkedList<BigInteger> encode = new LinkedList<>();
        LinkedList<BigInteger> decode = new LinkedList<>();
//        RSAMode ecb = new ECB_RSA();
        RSAMode ctr = new CTR_RSA();

        File file = new File("C:\\KingJoySaiy\\data.txt");
        try {
            Reader reader = new InputStreamReader(new FileInputStream(file));
            int tempchar;
            while ((tempchar = reader.read()) != -1) {
                if (((char) tempchar) != '\r') {
                    BigInteger p = new BigInteger(String.valueOf(tempchar));
                    all.add(p);
//                    System.out.print((char) tempchar);
                }
            }
            reader.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
//        encode = ecb.encryptBlock(all);
//        decode = ecb.decryptBlock(encode);
        encode = ctr.encryptBlock(all);
        decode = ctr.decryptBlock(encode);

        File file2 = new File("C:\\KingJoySaiy\\out.txt");
        try  {
            Writer writer = new OutputStreamWriter(new FileOutputStream(file2));
            char tmp;
            for (int i = 0; i < all.size(); i++) {
                tmp = (char)all.get(i).intValue();
                System.out.println(tmp);
                if (tmp == '\n') writer.write('\r');
                writer.write(tmp);
            }
            writer.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
