package Test;

import OperationMode.CTR_RSA;
import OperationMode.ECB_RSA;
import OperationMode.RSAMode;
import OperationMode.mixed_RSA;

import java.math.BigInteger;
import java.util.LinkedList;

public class simpleTest {   //对随机数进行测试

    private static void show(LinkedList<BigInteger> x) {

        for (BigInteger p : x) {
            System.out.print(p + " ");
        }
        System.out.println();
    }

    private static boolean test(RSAMode mode) {

        LinkedList<BigInteger> a = randData.randData();
        LinkedList<BigInteger> tmp = mode.encryptBlock(a);
        LinkedList<BigInteger> b = mode.decryptBlock(tmp);
        if (a.size() != b.size()) return false;
        for (int i = 0; i < a.size(); i++) {
            if (!a.get(i).equals(b.get(i))) return false;
        }
        show(a);
//        show(tmp);
        show(b);
        return true;
    }

    public static void run() {

        RSAMode ecb = new ECB_RSA();
        RSAMode ctr = new CTR_RSA();
        RSAMode fin = new mixed_RSA();
        System.out.println(test(ecb));
        System.out.println(test(ctr));
        System.out.println(test(fin));
    }
}
