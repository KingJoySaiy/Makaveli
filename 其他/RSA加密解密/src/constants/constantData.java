package Constants;

import java.math.BigInteger;

public class constantData {

    public static final BigInteger P = new BigInteger("10000019");     //约定RSA算法中P = 10000019, q = 10000079
    public static final BigInteger Q = new BigInteger("10000079");
    public static final BigInteger publicKey = new BigInteger("264474015");    //公钥E需满足: 1<E<φ[n], E与φ[P * Q]互质, 可设为264474015

//    public static final String filePath = "C:\\KingJoySaiy\\data.txt";    //初始待加密的文件目录
//    public static final String ciperFilePath = "C:\\KingJoySaiy\\cipherFile.txt";   //加密后的密文存储位置
//    public static final String plainFilePath = "C:\\KingJoySaiy\\plainFile.txt";    //解密后的明文存储位置
}
