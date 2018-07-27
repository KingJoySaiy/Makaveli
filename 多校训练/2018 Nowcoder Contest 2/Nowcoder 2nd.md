* [nowcoder contest 2](https://www.nowcoder.com/acm/contest/140#question)
## A. run （DP）
* **题目大意** ： 给定k，从0开始每次往前走1步或者跳k步，但不能连跳2次。对于q个查询`[l, r]`求抵达该区间内所有点的方案总和。
* **大体思路** ： 考虑`dp1[i]`记录走到位置i的方案数，`dp2[i]`记录跳到位置i的方案数。不难看出前者的状态转移方程为`dp1[i] = dp1[i - 1] + dp2[i - 1]`，表示可以走到`i - 1`再走到i或跳到`i - 1`再走到i； 后者是`dp2[i] = dp1[i - k]`，表示从`i - k`跳到i必须满足之前是走到`i - k`的。
 
```c++
#include <bits/stdc++.h>

using namespace std;

const int mod = int(1e9 + 7);
const int maxn = int(1e5 + 5);

long long res[maxn], dp[maxn];
int q, k, l, r;

int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> q >> k;
    for (int i = 0; i < k; i++) res[i] = 1;
    for (int i = k; i < maxn; i++) {
        res[i] = res[i - 1] + dp[i - 1] % mod;
        dp[i] = res[i - k];
    }
    res[0] = dp[0] = 0;
    for (int i = 1; i < maxn; i++) {
        (res[i] += res[i - 1] + dp[i]) %= mod;
    }

    while (q--) {
        cin >> l >> r;
        cout << (res[r] - res[l - 1] + mod) % mod << endl;
    }

    return 0;
}
```

## C. message （凸包 + 三分）
* **题目大意** ： 坐标系内有n条直线`y = a * x + b`，ab都给出。对于m次查询`y = c * x + d`，求直线与上述直线集合交点的大于0的横坐标最大值。
* **大体思路** ： 这题很考验思维啊，两直线交点横坐标为`(d - b) / (a - c)`，要求大于0的横坐标最大值即为求`(a, b), (c, d)`两点构成直线斜率相反数最大值，亦即斜率小于0的最小值。然后对于`(a, b)`点集用凸包维护，对于每个`(c, d)`可以在凸包中 **三分** 斜率最小值，由于三分的是 **离散型** 的索引值，所以不是比较三等分点而是比较`cost[mid]`和`cost[mid + 1]`，然后让`left`和`right`向中间聚拢即可。

```c++
#include <bits/stdc++.h>

using namespace std;

const int maxn = int(1e5 + 5);
int n, m;

struct data {

    double x, y, res;
    int id;
    bool operator < (data t) {
        return x < t.x or x == t.x and y < t.y;
    }
    double K(data t) {
        return (y - t.y) / (x - t.x);
    }
    double cross(data a,data b) {    //t->a cross t->b
        return (a.x - x) * (b.y - y) - (a.y - y) * (b.x - x);
    }
} a[maxn], s[maxn];

inline bool cmp(data a, data b) {

    return a.id < b.id;
}
void graham() {

    for (int i = 0, top = 0; i < m; i++) {
        if (!a[i].id) {      //id -> 0 ~ n - 1，加入凸包
            while (top > 1 and s[top - 2].cross(a[i], s[top - 1]) <= 0) top--;
            s[top++] = a[i];
        } else {              //id -> n ~ m - 1，在凸包中三分斜率最小值
            if (!top) continue;
            int l = 0, r = top - 1, m;
            while (l < r) {
                m = (l + r) / 2;
                if (a[i].K(s[m]) < a[i].K(s[m + 1])) r = m;
                else l = m + 1;
            }
            a[i].res = min(a[i].res, a[i].K(s[l]));
        }
    }
}
int main() {

    cin >> n;
    for (int i = 0; i < n; i++) scanf("%lf%lf", &a[i].x, &a[i].y);
    cin >> m;
    m += n;
    for (int i = n; i < m; i++)
        scanf("%lf%lf", &a[i].x, &a[i].y), a[i].id = i;

    sort(a, a + m);
    graham();
    reverse(a, a + m);
    graham();
    sort(a, a + m, cmp);

    for (int i = n; i < m; i++) {
        if (a[i].res < 0) printf("%.12f\n", -1 * a[i].res);
        else puts("No cross");
    }

    return 0;
}
```

## D. money （模拟）
* **题目大意** ： 给定n个数，从左往右可以花a[i]物品+1，可以物品-1获得a[i]，也可跳过。求最最大利润和最小操作次数。
* **大体思路** ： 从左往右扫一遍，极小值就买，极大值就卖。

```c++
#include <bits/stdc++.h>

using namespace std;

const int maxn = int(1e5 + 5);

int a[maxn], n, ct;

void solve() {

    long long res = 0, ct = 0;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    bool flag = true;
    int mi, t = 0;
    while (true) {
        if (flag) {
            while (t < n - 1 and a[t] >= a[t + 1]) t++;
            mi = a[t];
        } else {
            while (t < n - 1 and a[t] <= a[t + 1]) t++;
            res += a[t] - mi;
            ct++;
        }
        flag = !flag;
        if (t == n - 1) break;
    }
    cout << res << ' ' << 2 * ct << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> ct;
    while (ct--) solve();

    return 0;
}
```

## G. transform
## H. travel
## I. car （模拟）
## J. farm （随机化）