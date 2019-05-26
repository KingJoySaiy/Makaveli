import RSA.*;

import java.math.BigInteger;
import java.util.LinkedList;

import blockCipherMode.*;

class Test {

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
//        if (a.size() != b.size()) return false;
//        for (int i = 0; i < a.size(); i++) {
//            if (!a.get(i).equals(b.get(i))) return false;
//        }
        show(a);
//        show(tmp);
        show(b);
        return true;
    }
    public static void main(String[] args) {

        RSAMode ecb = new ECB_RSA("264474015");
        RSAMode ctr = new CTR_RSA("264474015");
        System.out.println(test(ecb));
        System.out.println(test(ctr));
    }
}
