package RSA;

import java.math.BigInteger;
import Constants.constantData;

public class RSADemo {

    private Algorithm AL;
    private BigInteger publicKey;

    public BigInteger encrypt(BigInteger plainText) {   //RSA加密（明文->密文）

        return AL.modPow(plainText, publicKey, AL.getN());
    }

    public BigInteger decrypt(BigInteger cipherText) {   //RSA解密（密文->明文）

        return AL.modPow(cipherText, AL.getPrivateKey(publicKey), AL.getN());
    }

    public RSADemo() {

        publicKey = constantData.publicKey;
        AL = new Algorithm();
    }
}
