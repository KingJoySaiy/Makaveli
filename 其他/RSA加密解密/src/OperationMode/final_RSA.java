package OperationMode;

import RSA.RSADemo;
import java.math.BigInteger;
import java.util.LinkedList;

public class final_RSA implements RSAMode {

    private RSADemo rsa;
    private BigInteger counter;
    private boolean modeFlag;   //选择分组工作方式
    public final_RSA() {

        rsa = new RSADemo();
    }
    public LinkedList<BigInteger> encryptBlock(LinkedList<BigInteger> plainTexts) {

        modeFlag = false;
        counter = BigInteger.ONE;
        LinkedList<BigInteger> res = new LinkedList<>();
        for (BigInteger p : plainTexts) {
            if (modeFlag) {
                res.add(rsa.encrypt(p));
            } else {
                res.add(rsa.encrypt(counter).xor(p));
                counter = counter.add(BigInteger.ONE);
            }
            modeFlag = !modeFlag;
        }
        return res;
    }
    public LinkedList<BigInteger> decryptBlock(LinkedList<BigInteger> cipherTexts) {

        modeFlag = false;
        counter = BigInteger.ONE;
        LinkedList<BigInteger> res = new LinkedList<>();
        for (BigInteger p : cipherTexts) {
            if (modeFlag) {
                res.add(rsa.decrypt(p));
            } else {
                res.add(rsa.encrypt(counter).xor(p));
                counter = counter.add(BigInteger.ONE);
            }
            modeFlag = !modeFlag;
        }

        return res;
    }
}