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

## C. message （凸包 + dp + 二分）
* **题目大意** ： 
* **大体思路** ： 

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