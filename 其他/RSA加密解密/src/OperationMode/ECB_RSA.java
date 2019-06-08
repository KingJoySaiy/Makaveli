package OperationMode;

import RSA.RSADemo;
import java.math.BigInteger;
import java.util.LinkedList;

public class ECB_RSA implements RSAMode{

    private RSADemo rsa;
    public ECB_RSA() {

        rsa = new RSADemo();
    }
    public LinkedList<BigInteger> encryptBlock(LinkedList<BigInteger> plainTexts) {

        LinkedList<BigInteger> res = new LinkedList<>();
        for (BigInteger p : plainTexts) {   //对于每个分组依次加密
            res.add(rsa.encrypt(p));
        }
        return res;
    }
    public LinkedList<BigInteger> decryptBlock(LinkedList<BigInteger> cipherTexts) {

        LinkedList<BigInteger> res = new LinkedList<>();
        for (BigInteger p : cipherTexts) {  //对于每个分组依次解密
            res.add(rsa.decrypt(p));
        }
        return res;
    }
}
