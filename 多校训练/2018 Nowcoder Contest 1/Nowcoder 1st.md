* [nowcoder contest 1](https://www.nowcoder.com/acm/contest/139/#question)
## A. Monotonic Matrix （LGV + DP + 组合数学）
* **题目大意** ： 给定n, m表示n×m的矩阵，所有点只能填`0, 1, 2`且每个点的数值小于等于右边及下面的数值，求方案数对(1e9 + 7)取模。
* **大体思路** ： 填充方案数实际就是01和12分界线的方案数，即从`(n, 0)`到`(0, m)`的两条可重合但不相交的分界线方案数。可进一步转换为从`(n, 0)`到`(0, m)`和从`(n - 1, -1)`到`(-1, m - 1)`的两条严格不相交的路径。利用[LGV算法](https://en.wikipedia.org/wiki/Lindstr%C3%B6m%E2%80%93Gessel%E2%80%93Viennot_lemma)得到答案。组合数利用 **杨辉三角** 打表即可。 （矩阵规格是`n*m`的但路径规格是`(n+1)*(m+1)`，一开始连这个都看错了噗）

<img src="_image/A_1.jpg" width="600" height="300" />

```c++
#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int maxn = 2005;
const int mod = int(1e9 + 7);
LL c[maxn][maxn];
int n, m;

void ini() {

    for (int n = 0; n < maxn; n++) {
        c[n][0] = c[n][n] = 1;
        for (int i = 1; i < n; i++)
            c[n][i] = (c[n - 1][i] + c[n - 1][i - 1]) % mod;
    }
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    ini();
    while (cin >> n >> m) {
        cout << (c[n + m][n] * c[n + m][n] % mod - c[n + m][n - 1] * c[n + m][m - 1] % mod + mod) % mod << endl;
    }

    return 0;
}
```

* 类似题目：[codeforces 348D](https://codeforces.com/contest/348/problem/D)，问在有障碍图中从左上到右下的两条不同路线的方案数。[代码](https://github.com/KingJoySaiy/Iterator/blob/master/%E5%A4%9A%E6%A0%A1%E8%AE%AD%E7%BB%83/2018%20Nowcoder%20Contest%201/code/cf_948d.cpp)

## B. Symmetric Matrix （DP + 组合数学）
* **题目大意** ： 在n阶方阵中每行和必须为2，数字只能是`0, 1, 2`求方阵的方案数。
* **大体思路** ： 题意可以转换为有n个节点的无向图，所有节点的度为2，允许有重边但不能有自环，求满足条件的图的个数。考虑用求 **动态规划** 的递推式，`dp[n]`表示前n个节点构成的图的方案数。可以从前`n - 1`个节点任选一个出来与新节点构图这两个节点间有2个重边，则节点的度都为2满足条件，得出`dp[n] = (n - 1) * dp[n - 2]`。再扩展到一般情况，保留前`n - 1`个节点中k个节点的边，剩余的`n - 1 - k`个节点按照任意排列与新节点构成新的邻接矩阵，再加上上述特殊情况，得到如下递推式：

<img src="_image/B_1.gif" width="600" height="120" />

为消去sigma符号，可以利用`f[n] - (n - 1) * f[n - 1]`错位相减即可得到第二个式子。
(数据范围n的总和不超过`1e7`，所以针对每组输入直接递推输出第n项即可。本来想进一步简化求出 **通项公式** 或用 **矩阵快速幂** 的，能力有限没搞出来=_=)

```c++
#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int maxn = int(1e5 + 5);
LL f[maxn], n, mod;

void solve() {

    f[0] = f[1] = 0ll % mod;
    f[2] = f[3] = 1ll % mod;
    for (LL i = 4ll; i <= n; i++) {
        f[i] = ((i - 1) * f[i - 1] % mod
                + (i - 1) * f[i - 2] % mod
                - (i - 1) * (i - 2) / 2 % mod * f[i - 3] % mod
                + mod) % mod;
    }
    cout << f[n] << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n >> mod) solve();

    return 0;
}
/*
f(x) = (n - 1) * [f(n - 1) + f(n - 2)] - (n - 1) * (n - 2) / 2 * f(n - 3)
value: 0, 0, 1, 1, 6, 22 ...
index: 0, 1, 2, 3, 4, 5  ...
 */
```

## D. Two Graphs (枚举 + 图论）
* **题目大意** ： 给定2个最多8个节点的无向图，两个图都有n个节点且无重边。求从图2中选出多少种映射方案使之与图1同构。
* **大体思路** ： 用`1-n`的全排列枚举`n!`种映射方案，若保证是双射 （ 即图1中i-j的边x都对应图2中某边f(x) ） ，则将`pair(i, j)`塞进set中去重。实践证明可以将二维邻接矩阵下标(i, j)转换为一维(i * n + j)以实现去重，不会爆64位int。
```c++
#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int maxn = 10;
bool a[maxn][maxn], b[maxn][maxn];
unordered_set<LL> all;
int f[maxn];
int n, m1, m2, x, y;

void solve() {

    memset(a, false, sizeof(a));
    memset(b, false, sizeof(b));
    for (int i = 0; i < n; i++) f[i] = i;
    all.clear();

    while (m1--) {
        cin >> x >> y; x--, y--;
        a[x][y] = a[y][x] = true;
    }
    while (m2--) {
        cin >> x >> y; x--, y--;
        b[x][y] = b[y][x] = true;
    }
    do {
        LL t = 0ll;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (!a[i][j]) continue;
                if (b[x = f[i]][y = f[j]]) {
                    if (x > y) swap(x, y);
                    t |= LL(1) << (x * n + y);
                } else goto ed;
            }
        }
        all.insert(t);
        ed: continue;
    } while (next_permutation(f, f + n));
    cout << all.size() << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n >> m1 >> m2) solve();

    return 0;
}
```
## E. Removal （DP）
## F. Sum of Maximum （拉格朗日插值）
