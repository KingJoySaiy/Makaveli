package RSA;

import java.math.BigInteger;
import java.util.regex.Pattern;

public class RSADemo {

    class invalidKeyException extends Exception {   //公钥非法异常类

        invalidKeyException() {
            super("非法公钥！");
        }
    }

    private Algorithm AL;
    private BigInteger publicKey;

    public BigInteger encrypt(BigInteger plainText) {   //RSA加密（明文->密文）

        return AL.modPow(plainText, publicKey, AL.getN());
    }

    public BigInteger decrypt(BigInteger cipherText) {   //RSA解密（密文->明文）

        return AL.modPow(cipherText, AL.getPrivateKey(publicKey), AL.getN());
    }

    public RSADemo(String Key) {    //传入公钥

        try {
            if (!Pattern.compile("[0-9]*").matcher(Key).matches()) {    //正则表达式判断Key是否都是数字
                throw new invalidKeyException();
            }
            publicKey = new BigInteger(Key);    //将公钥和AL对象初始化
            AL = new Algorithm();

            if (!AL.checkPublicKey(publicKey)) {    //若公钥不合法也抛出异常
                throw new invalidKeyException();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
