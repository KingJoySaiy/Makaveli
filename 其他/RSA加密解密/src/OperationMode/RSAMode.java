package OperationMode;

import java.math.BigInteger;
import java.util.LinkedList;

public interface RSAMode {  //RSA算法分组工作接口

    LinkedList<BigInteger> encryptBlock(LinkedList<BigInteger> plainTexts);
    LinkedList<BigInteger> decryptBlock(LinkedList<BigInteger> cipherTexts);
}
