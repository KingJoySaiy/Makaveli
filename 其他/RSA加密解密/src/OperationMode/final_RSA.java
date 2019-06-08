package OperationMode;

import RSA.RSADemo;
import Constants.constantData;
import java.math.BigInteger;
import java.util.LinkedList;

public class final_RSA implements RSAMode {

    private RSADemo rsa;
    private BigInteger counter;
    private boolean flag;
    public final_RSA() {

        counter = constantData.counter;
        flag = constantData.modeFlag;
        rsa = new RSADemo();
    }
    public LinkedList<BigInteger> encryptBlock(LinkedList<BigInteger> plainTexts) {

        LinkedList<BigInteger> res = new LinkedList<>();
        for (int i = 0; i < plainTexts.size(); i++) {
            if (!flag) {
                res.add(rsa.encrypt(plainTexts.get(i)));
            } else {
                res.add(rsa.encrypt(plainTexts.get(i)).xor(counter));
                counter = counter.add(BigInteger.ONE);
            }
            flag = !flag;
        }
        return res;
    }
    public LinkedList<BigInteger> decryptBlock(LinkedList<BigInteger> cipherTexts) {

        LinkedList<BigInteger> res = new LinkedList<>();
        for (int i = cipherTexts.size() - 1; i >= 0; i--) {
            if (flag) {
                res.addFirst(rsa.decrypt(cipherTexts.get(i)));
            } else {
                counter = counter.subtract(BigInteger.ONE);
                res.addFirst(rsa.decrypt(cipherTexts.get(i).xor(counter)));
            }
            flag = !flag;
        }
        return res;
    }
}