package OperationMode;

import java.math.BigInteger;
import java.util.LinkedList;

import RSA.RSADemo;

public class CTR_RSA implements RSAMode {

    private RSADemo rsa;
    public CTR_RSA() {

        rsa = new RSADemo();
    }
    public LinkedList<BigInteger> encryptBlock(LinkedList<BigInteger> plainTexts) {

        BigInteger counter = BigInteger.ONE;
        LinkedList<BigInteger> res = new LinkedList<>();
        for (BigInteger p : plainTexts) {
            res.add(rsa.encrypt(counter).xor(p));   //每次将counter加密后与明文进行抑或得到密文
            counter = counter.add(BigInteger.ONE);
        }
        return res;
    }
    public LinkedList<BigInteger> decryptBlock(LinkedList<BigInteger> cipherTexts) {

        return encryptBlock(cipherTexts);    //再次将counter加密后与密文进行抑或得到明文
    }
}
