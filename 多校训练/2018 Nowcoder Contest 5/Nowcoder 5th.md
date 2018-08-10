* [nowcoder contest 5](https://www.nowcoder.com/acm/contest/143#question)

## A. gpa （01分数规划 + 二分）
* **题目大意** ：给定数组s和c，分别删掉k个数。求`sigma(s[i] * c[i]) / sigma(s[i])`最大值。 
* **大体思路** ：简单的 **01分数规划** 问题，设答案为res，则有`sigma(s[i] * c[i]) = res * sigma(s[i])`，进一步转化为`sigma(s[i] * (c[i] - res)) = 0`。从而可以 **二分** 答案，每次取前`n - k`大的数，若小于0则res取大了，否则取小了。
```c++
#include <bits/stdc++.h>

using namespace std;

const int maxn = int(1e5 + 5);
double s[maxn], c[maxn], a[maxn];
int n, k, ct = 30;

int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> s[i];
    for (int i = 0; i < n; i++) cin >> c[i];

    double l = 0, r = 1000, mid, res;
    while (ct--) {
        mid = (r + l) / 2, res = 0;
        for (int i = 0; i < n; i++) a[i] = s[i] * (c[i] - mid);
        sort(a, a + n);
        for (int i = n - 1; i >= k; i--) res += a[i];
        if (res >= 0) l = mid;
        else r = mid;
    }
    cout << fixed << setprecision(8) << l << endl;

    return 0;
}

```

## E. room (二分图匹配 + 费用流)
（占坑）

## F. take （线段树 + 逆元 + 数学期望）
（占坑）

## G. max （gcd）
* **题目大意** ：给定n和k，求`[1, n]`中2数gcd位k的乘积最大值。
* **大体思路** ：显然问题可以转化为`[1, n / k]`中2个 **互质数** 的乘积最大值乘以k平方。若有解必然k要小于n，要满足2数乘积最大且互质，若`n / k == 1`则这2数都是1，否则必然是`n / k - 1, n / k`。

```c++
#include <bits/stdc++.h>
using namespace std;
long long n, k, t, res;

int main() {

    cin >> k >> n;
    if (k >= n) {
        puts("-1");
        return 0;
    }
    t = n / k;
    res = k * k;
    cout << (t == 1 ? res : res * t * (t - 1)) << endl;

    return 0;
}
```

## J. plan （模拟）
* **题目大意** ：n个人订房，双人间价格p2，三人间价格p3，求最小花费。
* **大体思路** ：令`m = min(p2, p3)`只有4种情况：先全订p2若多出1人则加m；先全订p3若多出1/2人则加m；先全订p2多出3人加p3；先全订p3多出4人加`2 * p2`。判断一下几个条件取最小值即可。
```c++
#include <bits/stdc++.h>
using namespace std;
long long n, p2, p3, x, res;

int main() {

    cin >> n >> p2 >> p3;
    x = min(p2, p3);
    res = min(n / 3 * p3 + (n % 3 ? x : 0), n / 2 * p2 + (n % 2 ? x : 0));
    if (n % 3 == 1) res = min(res, (n - 4) / 3 * p3 + 2 * p2);
    if (n % 2 == 1) res = min(res, (n - 3) / 2 * p2 + p3);
    cout << res << endl;

    return 0;
}

```

