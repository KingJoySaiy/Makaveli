import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.math.BigInteger;

public class Main {
    private static String[] s = new String[2000];
    private static int[] ls = new int[4000];
    private static int[] rs = new int[4000];
    private static BigInteger[] siz = new BigInteger[4000];
    private static BigInteger[][] dp = new BigInteger[2][4000];
    private static void dfs(int x) {
        if (ls[x] == 0) {
            siz[x] = BigInteger.valueOf(2);
            dp[0][x] = dp[1][x] = BigInteger.valueOf(1);
        } else {
            dfs(ls[x]);
            dfs(rs[x]);
            siz[x] = siz[ls[x]].multiply(siz[rs[x]]);
            dp[0][x] = dp[1][x] = BigInteger.valueOf(0);
            for (int i = 0; i < 16; ++i) {
                if (s[x].charAt(i) == '0') continue;
                for (int j = 0; j < 4; ++j) {
                    int a = j & 1, b = j >> 1;

                    BigInteger[] l = new BigInteger[2];
                    l[a] = dp[a][ls[x]];
                    l[a ^ 1] = siz[ls[x]].subtract(l[a]);

                    BigInteger[] r = new BigInteger[2];
                    r[b] = dp[b][rs[x]];
                    r[b ^ 1] = siz[rs[x]].subtract(r[b]);

                    BigInteger _f = BigInteger.valueOf(0);
                    BigInteger _g = BigInteger.valueOf(0);

                    for (int k = 0; k < 4; ++k) {
                        BigInteger tmp = l[k >> 1].multiply(r[k & 1]);
                        if (((i >> k) & 1) > 0) {
                            _f = _f.add(tmp);
                        } else {
                            _g = _g.add(tmp);
                        }
                    }

                    if (dp[0][x].compareTo(_g) < 0) {
                        dp[0][x] = _g;
                    }
                    if (dp[1][x].compareTo(_f) < 0) {
                        dp[1][x] = _f;
                    }
                }
            }
        }
    }
    public static void main(String[] argv) {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        try {
            int T = Integer.valueOf(bufferedReader.readLine());
            for (int t = 1; t <= T; ++t) {
                int n = Integer.valueOf(bufferedReader.readLine());
                for (int i = 1; i < n << 1; ++ i){
                    ls[i] = rs[i] = 0;
                }
                for (int i = 1; i < n; ++i) {
                    s[i] = bufferedReader.readLine();
                }
                for (int i = 2; i < (n << 1); ++i) {
                    int a = Integer.valueOf(bufferedReader.readLine());
                    if (rs[a] < i) {
                        ls[a] = rs[a];
                        rs[a] = i;
                    } else {
                        ls[a] = i;
                    }
                }
                dfs(1);
                System.out.println(String.format("Case #%d: ", t) + dp[1][1].toString());
            }
        } catch (Throwable e) {
            e.printStackTrace();
        }
    }
}
