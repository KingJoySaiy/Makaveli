import java.io.*;
import java.math.BigInteger;
import java.util.LinkedList;
import java.util.Scanner;

import OperationMode.*;

class fileWork {

    private RSAMode ecb, ctr, mixed;    //三种分组密码工作模式对象
    private LinkedList<BigInteger> data;    //临时存储BigInteger序列

    fileWork() {

        ecb = new ECB_RSA();
        ctr = new CTR_RSA();
        mixed = new mixed_RSA();
        data = new LinkedList<>();
    }

    private LinkedList<BigInteger> deserialization(File inputFile) {   //按字节读文件到BigInteger链表（反序列化）

        LinkedList<BigInteger> res = new LinkedList<>();
        try {
            Reader reader = new InputStreamReader(new FileInputStream(inputFile));
            int tmp;
            while ((tmp = reader.read()) != -1) {
                BigInteger p = new BigInteger(String.valueOf(tmp));
                res.add(p);
            }
            reader.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return res;
    }

    private void serialization(LinkedList<BigInteger> data, File outputFile) {   //将BigInteger链表写入文件（序列化）

        try {
            Writer writer = new OutputStreamWriter(new FileOutputStream(outputFile));
            int tmp;
            for (int i = 0; i < data.size(); i++) {
                tmp = data.get(i).intValue();
                writer.write(tmp);  //将8位ASCII码值写入文件
            }
            writer.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    void encryptFile(File file, int mode) { //加密文件

        data = deserialization(file);  //读取明文到BigInteger链表
        if (mode == 1) {    //依据选择的模式，将明文加密成密文
            data = mixed.encryptBlock(data);
        } else if (mode == 2) {
            data = ecb.encryptBlock(data);
        } else {
            data = ctr.encryptBlock(data);
        }
        try {
            Writer writer = new OutputStreamWriter(new FileOutputStream(file));
            for (int i = 0; i < data.size(); i++) { //将加密后的BigInteger密文按行写入文件
                writer.write(data.get(i).toString() + "\n");
            }
            writer.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    void decryptFile(File file, int mode) { //解密文件

        data.clear();   //清空data
        try {
            Scanner in = new Scanner(file);
            while (in.hasNext()) {  //将密文按行取出
                data.add(new BigInteger(in.next()));
            }
            in.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        if (mode == 1) {//依据选择的模式，对密文分组进行解密
            data = mixed.decryptBlock(data);
        } else if (mode == 2) {
            data = ecb.decryptBlock(data);
        } else {
            data = ctr.decryptBlock(data);
        }
        serialization(data, file);  //解密后的明文写入文件
    }
}
