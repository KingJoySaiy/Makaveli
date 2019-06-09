package Test;

import java.math.BigInteger;
import java.util.LinkedList;
import java.util.Random;

public class randData { //随机生成数据

    public static LinkedList<BigInteger> randData() {

        Random random = new Random(233);
        LinkedList<BigInteger> res = new LinkedList<>();
        int count = random.nextInt(10) + 10;    //随机生成10~20个数
        while (count-- != 0) {
            res.add(new BigInteger(String.valueOf(Math.abs(random.nextInt()))));
        }
        return res;
    }
}
