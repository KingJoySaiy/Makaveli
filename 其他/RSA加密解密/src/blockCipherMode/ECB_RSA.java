package blockCipherMode;

import RSA.RSADemo;
import java.math.BigInteger;
import java.util.LinkedList;

public class ECB_RSA implements RSAMode{

    private RSADemo rsa;
    public ECB_RSA(String Key) {

        rsa = new RSADemo(Key);
    }
    public LinkedList<BigInteger> encryptBlock(LinkedList<BigInteger> plainTexts) {

        LinkedList<BigInteger> res = new LinkedList<>();
        for (BigInteger p : plainTexts) {
            res.add(rsa.encrypt(p));
        }
        return res;
    }
    public LinkedList<BigInteger> decryptBlock(LinkedList<BigInteger> cipherTexts) {

        LinkedList<BigInteger> res = new LinkedList<>();
        for (BigInteger p : cipherTexts) {
            res.add(rsa.decrypt(p));
        }
        return res;
    }
}
