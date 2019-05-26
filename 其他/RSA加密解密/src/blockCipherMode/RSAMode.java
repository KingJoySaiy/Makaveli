package blockCipherMode;

import java.math.BigInteger;
import java.util.LinkedList;

public interface RSAMode {
    LinkedList<BigInteger> encryptBlock(LinkedList<BigInteger> plainTexts);
    LinkedList<BigInteger> decryptBlock(LinkedList<BigInteger> cipherTexts);
}
