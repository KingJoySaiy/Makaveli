package OperationMode;

import RSA.RSADemo;
import java.math.BigInteger;
import java.util.LinkedList;

public class mixed_RSA implements RSAMode { //混合分组工作模式

    private RSADemo rsa;
    private BigInteger counter;
    private boolean modeFlag;   //选择分组工作方式（交替使用ECB和CTR模式）
    public mixed_RSA() {
        rsa = new RSADemo();
    }
    public LinkedList<BigInteger> encryptBlock(LinkedList<BigInteger> plainTexts) { //分组加密

        modeFlag = false;
        counter = BigInteger.ONE;
        LinkedList<BigInteger> res = new LinkedList<>();
        for (BigInteger p : plainTexts) {   //ECB模式与CTR模式交替使用
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
    public LinkedList<BigInteger> decryptBlock(LinkedList<BigInteger> cipherTexts) {    //分组解密

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