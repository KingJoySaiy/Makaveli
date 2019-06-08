package constants;

import java.math.BigInteger;

public class constantData {

    public static final BigInteger P = new BigInteger("10000019");     //约定RSA算法中P = 10000019, q = 10000079
    public static final BigInteger Q = new BigInteger("10000079");
    public static final BigInteger publicKey = new BigInteger("264474015");    //公钥E需满足: 1<E<φ[n], E与φ[P * Q]互质, 可设为264474015
}
