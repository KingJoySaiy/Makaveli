package RSA;

import java.math.BigInteger;
import Constants.constantData;

class Algorithm {

    private BigInteger n, EulerN;   //公共模n，欧拉函数第n项

    BigInteger modPow(BigInteger x, BigInteger n, BigInteger mod) { //快速幂算法求 x^n % mod

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
    private static BigInteger inverse(BigInteger a, BigInteger b, BigInteger x, BigInteger y) {    //扩展欧几里得求逆元，x和y初始值为1和0

        BigInteger res = x.subtract(a.divide(b).multiply(y));
        if (a.mod(b).equals(BigInteger.ONE)) {
            return res;
        } else {
            return inverse(b, a.mod(b), y, res);
        }
    }

    BigInteger getPrivateKey(BigInteger publicKey) {    //根据公钥求私钥 (二者在模φ[n]下互为逆元)

        return inverse(publicKey, EulerN, BigInteger.ONE, BigInteger.ZERO);
    }
    BigInteger getN() {     //获取公共模数n

        return n;
    }
    Algorithm() {

        BigInteger p = constantData.P, q = constantData.Q;
        n = p.multiply(q);      //根据P和Q将n和φ[n]初始化
        EulerN = p.subtract(BigInteger.ONE).multiply(q.subtract(BigInteger.ONE));
    }

}
