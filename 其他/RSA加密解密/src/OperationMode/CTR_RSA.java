package OperationMode;

import java.math.BigInteger;
import java.util.LinkedList;

import RSA.RSADemo;

public class CTR_RSA implements RSAMode {

    private RSADemo rsa;
    private BigInteger counter;
    public CTR_RSA() {

        counter = BigInteger.ONE;
        rsa = new RSADemo();
    }
    public LinkedList<BigInteger> encryptBlock(LinkedList<BigInteger> plainTexts) {

        LinkedList<BigInteger> res = new LinkedList<>();
        for (BigInteger p : plainTexts) {
            res.add(rsa.encrypt(p).xor(counter));   //每次将密文与counter进行抑或运算
            counter = counter.add(BigInteger.ONE);
        }
        return res;
    }
    public LinkedList<BigInteger> decryptBlock(LinkedList<BigInteger> cipherTexts) {

        LinkedList<BigInteger> res = new LinkedList<>();
        for (int i = cipherTexts.size() - 1; i >= 0; i--) {
            counter = counter.subtract(BigInteger.ONE);
            res.addFirst(rsa.decrypt(cipherTexts.get(i).xor(counter)));
        }
        return res;
    }
}
