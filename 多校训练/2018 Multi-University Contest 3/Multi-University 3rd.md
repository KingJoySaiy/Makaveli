* [Multi-University contest 3](http://acm.hdu.edu.cn/userloginex.php?cid=804)

## 1001. Ascending Rating （单调双端队列）
* **题目大意** ： 长度为n的序列的长度为m的子序列中，分别求最大值和起始下标的异或和，最大值改变次数和起始下标的异或和。
* **大体思路** ： 前k项直接给出，后面的可以通过给定的递推式求出。易知，对于子序列中的最大值前面的数，之后不可能用到，故可以再也不考虑。而之后比该数大的数会影响到最大值改变次数，故正向处理不可取。尝试用 **双端队列** 记录最大值集合的索引，反向处理从而下标降序。每插入一个数，将队尾的`(序列中在该数前的)`小于等于该数的删去，故队列中的值也是降序的。这样就能维护每个 **子序列最大值** ，最大值改变次数即为双端队列中元素个数。本题很 **友好** 的不卡STL，可以不用数组模拟。
```c++
#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int maxn = int(1e7 + 5);
LL a[maxn], p, q, r, mod, res1, res2;
deque<LL> que;
int ct, n, m, k;

void solve() {

    cin >> n >> m >> k >> p >> q >> r >> mod;
    for (int i = 1; i <= n; i++) {
        if (i > k) a[i] = (p * a[i - 1] + q * i + r) % mod;
        else cin >> a[i];
    }

    que.clear();
    res1 = res2 = 0;
    for (int i = n; i >= 1; i--) {
        while (!que.empty() and a[i] >= a[que.back()]) que.pop_back();
        que.push_back(i);
        while (!que.empty() and que.front() > i + m - 1) que.pop_front();
        if (i <= n - m + 1) {
            res1 += a[que.front()] xor i;
            res2 += que.size() xor i;
        }
    }
    cout << res1 << ' ' << res2 << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> ct;
    while (ct--) solve();

    return 0;
}
```

## 1004. Euler Function (欧拉函数 + 打表找规律)
* **题目大意** ： 对于 **欧拉函数** `φ(n) = x`，若x是和数则将n添到序列中，求序列中第k个数。
* **大体思路** ：打出欧拉函数表，对每个值进行素数判断打出序列表，发现序列是`5, 8, 9, 10, 11, 12...`，大胆猜测第一个数为5其余数都是`k + 5`。

```c++
#include <bits/stdc++.h>
using namespace std;
int n, ct;

int main() {

    cin >> ct;
    while (ct--) {
        scanf("%d", &n);
        printf("%d\n", n == 1 ? 5 : n + 5);
    }
    
    return 0;
}
```

## 1006. Grab The Tree （博弈论 / 线性积 / 树形dp）
* **题目大意** ： 给定一个带权树，Alice（开玩笑）选不相邻的若干节点，剩下的是Bob的。分别求异或和，问最后胜者。
* **大体思路** ：一道很好的思维题，用 **线性积** 或 **树形dp** 就想复杂了。先考虑所有数异或和为0，先手不管怎么选都是平局；若异或和非零，设异或和 **最高非零位** 为`id`，则先手只需选`id`位为1的某一个数就能赢了，因为其余高位异或和为0，而`id`位由于改变 **奇偶性** ，其异或和也为0，故剩余数的异或和必然比该数小。
```c++
#include <bits/stdc++.h>

using namespace std;

int n, t, x, ct, res;

void solve() {

    cin >> n;
    res = 0, t = n;
    while (t--) {
        cin >> x;
        res ^= x;
    }
    while (--n) cin >> x >> t;
    cout << (res ? 'Q' : 'D') << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> ct;
    while (ct--) solve();

    return 0;
}
```

## 1007. Interstellar Travel （凸包 + 单调栈）
* **题目大意** ： 给定n个点的坐标，从1出发到n，每次花费两点叉积。在花费最小情况下，输出字典序最小的路径。
* **大体思路** ： 考虑到 **两点坐标叉积** 的几何意义是该两点与圆点围成的三角形面积2倍，若OA **斜率** 小于OB则叉积表示面积的-2倍。为了让叉积和最小，每次选的点必须大于前者斜率才能让每次叉积值为负，即路线是沿着 **凸包的上凸壳** 行走的。若出现 **多点共线** 的情况，则只要选下标最小的点，用一个 **单调栈** 维护相对斜率即可。
```c++
#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int maxn = int(2e5 + 5);
struct data {

    int id;
    LL x, y;
    bool operator < (const data &t) const {
        return x < t.x or (x == t.x and y > t.y) or (x == t.x and y == t.y and id < t.id);
    }
} a[maxn];
int s[maxn], top, n, ct;
LL tt;

inline bool check(int A, int B, int p) {

    return (tt = (a[p].y - a[A].y) * (a[B].x - a[A].x) - (a[p].x - a[A].x) * (a[B].y - a[A].y)) > 0
        or !tt and a[p].id < a[B].id;
}
void solve() {

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
        a[i].id = i;
    }
    sort(a, a + n);
    s[top = 1] = a[0].id;
    for (int i = 1; i < n; i++) {
        if (a[i].x == a[i - 1].x and a[i].y == a[i - 1].y) continue;
        while (top > 1 and check(s[top - 2], s[top - 1], i)) top--;
        s[top++] = i;
    }
    for (int i = 0; i < top; i++) cout << a[s[i]].id + 1 << " \n"[i == top -1];
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> ct;
    while (ct--) solve();

    return 0;
}
```

## 1012. Visual Cube （大模拟）
* **题目大意** ： 给定立方体的长宽高，画出3D视图。
* **大体思路** ： 正面，上底面，右侧面分别看规律改字符即可。

```c++
#include <bits/stdc++.h>

using namespace std;

const int maxn = 200;
int n, m, a, b, c, ct;
char res[maxn][maxn];

int main() {

    cin >> ct;
    while (ct--) {
        cin >> a >> b >> c;
        n = 2 * b + 2 * c + 1, m = 2 * a + 2 * b + 1;
        for (int i = 0; i < maxn; i++) {
            for (int j = 0; j < maxn; j++) {
                res[i][j] = '.';
            }
        }
        for (int i = 2 * b; i < n; i++) {
            if (i % 2 == 0) {
                for (int j = 0; j < 2 * a + 1; j++) res[i][j] = ((j % 2) ? '-' : '+');
            } else {
                for (int j = 0; j < 2 * a + 1; j += 2) res[i][j] = '|';
            }
        }
        for (int i = 0; i < 2 * b + 1; i++) {
            int st = 2 * b - i, ed = m - i;
            if (i % 2 == 0) {
                for (int j = st; j < ed; j++) res[i][j] = ((j % 2) ? '-' : '+');
            } else {
                for (int j = st; j < ed; j += 2) res[i][j] = '/';
            }
        }
        for (int j = m - 1; j >= m - 2 * b; j--) {
            int st = m - j, ed = m - j + 2 * c;
            if (j % 2 == 0) {
                for (int i = st; i < ed; i++) res[i][j] = ((i % 2) ? '|' : '+');
            } else {
                for (int i = st + 1; i < ed; i += 2) res[i][j] = '/';
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) cout << res[i][j];
            cout << endl;
        }
    }

    return 0;
}
```
