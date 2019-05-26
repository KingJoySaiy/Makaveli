package RSA;

import java.math.BigInteger;

class Algorithm {

    private BigInteger n, EulerN;   //公共模n，欧拉函数第n项

    BigInteger modPow(BigInteger x, BigInteger n, BigInteger mod) { //快速幂取模

        BigInteger res = BigInteger.ONE, two = new BigInteger("2");
        while (n.compareTo(BigInteger.ZERO) > 0) {
            if (n.mod(two).equals(BigInteger.ONE)) {
                res = res.multiply(x).mod(mod);
            }
            x = x.multiply(x).mod(mod);
            n = n.divide(two);
        }
        return res;
    }
    private static BigInteger inverse(BigInteger a, BigInteger b, BigInteger x, BigInteger y) {    //扩展欧几里得求逆元

        BigInteger res = x.subtract(a.divide(b).multiply(y));
        if (a.mod(b).equals(BigInteger.ONE)) {
            return res;
        } else {
            return inverse(b, a.mod(b), y, res);
        }
    }
    private BigInteger GCD(BigInteger a, BigInteger b) {    //最大公约数

        if(b.equals(BigInteger.ZERO)) return a;
        return GCD(b, a.mod(b));
    }

    boolean checkPublicKey(BigInteger E) {    //判断公钥E是否合法 (1<E<φ[n], E与φ[n]互质)

        return E.compareTo(BigInteger.ONE) > 0
                && E.compareTo(EulerN) < 0
                && GCD(E, EulerN).equals(BigInteger.ONE);
    }
    BigInteger getPrivateKey(BigInteger publicKey) {    //公钥求私钥 (二者在模φ[n]下互为逆元)

        return inverse(publicKey, EulerN, BigInteger.ONE, BigInteger.ZERO);
    }
    BigInteger getN() {     //获取公共模数n

        return n;
    }
    Algorithm() {

        BigInteger p = new BigInteger("10000019");   //约定该RSA算法中p=10000019, q=10000079
        BigInteger q = new BigInteger("10000079");
        //(p-1)*(q-1)的质因子为： 2 7 11 23 67 1523 19763
        //可令公钥为 (15 * 13 * 13 * 17 * 17 * 19 * 19) = 264474015
        n = p.multiply(q);      //根据P和Q将n和φ[n]初始化
        EulerN = p.subtract(BigInteger.ONE).multiply(q.subtract(BigInteger.ONE));
    }

}
