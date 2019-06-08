import OperationMode.CTR_RSA;
import OperationMode.ECB_RSA;
import OperationMode.RSAMode;
import OperationMode.final_RSA;
import Constants.constantData;
import Test.simpleTest;

import java.io.*;
import java.math.BigInteger;
import java.util.LinkedList;

class Main {

    private static LinkedList<BigInteger> read(String inputFilePath) {

        LinkedList<BigInteger> res = new LinkedList<>();
        File file = new File(inputFilePath);
        try {
            Reader reader = new InputStreamReader(new FileInputStream(file));
            int tmp;
            while ((tmp = reader.read()) != -1) {
                if (((char) tmp) != '\r') {
                    BigInteger p = new BigInteger(String.valueOf(tmp));
                    res.add(p);
                }
            }
            reader.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return res;
    }

    public static void write(LinkedList<BigInteger> data, String outputFilePath) {

        File file2 = new File(outputFilePath);
        try {
            Writer writer = new OutputStreamWriter(new FileOutputStream(file2));
            int tmp;
            for (int i = 0; i < data.size(); i++) {
                tmp = data.get(i).intValue();
                if ((char)tmp == '\n') writer.write('\r');
                writer.write(tmp);
            }
            writer.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void run() {

        RSAMode ecb = new ECB_RSA();
        RSAMode ctr = new CTR_RSA();
        RSAMode fin = new final_RSA();

        LinkedList<BigInteger> all = read(constantData.originFilePath);
        LinkedList<BigInteger> encode = null;
        LinkedList<BigInteger> decode = null;

//        encode = ecb.encryptBlock(all);
//        decode = ecb.decryptBlock(encode);
//        encode = ctr.encryptBlock(all);
//        decode = ctr.decryptBlock(encode);
        encode = fin.encryptBlock(all);
        decode = fin.decryptBlock(encode);

        write(encode, constantData.ciperFilePath);
        write(decode, constantData.plainFilePath);
    }

    public static void main(String[] args) {

//        run();
        simpleTest.run();
    }
}
