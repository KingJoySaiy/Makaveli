* [nowcoder contest 5](https://www.nowcoder.com/acm/contest/143#question)
* [nowcoder contest 6](https://www.nowcoder.com/acm/contest/144#question)
## 5_A. gpa （01分数规划 + 二分）
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

## 5_E. room (二分图匹配 + 费用流)
（占坑）

## 5_F. take （线段树 + 逆元 + 数学期望）
（占坑）

## 5_G. max （gcd）
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

## 5_J. plan （模拟）
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

## 6_A. Singing Contest （模拟）
* **题目大意** ： 2n个人分别有n个得分，两两进行n轮pk高分获胜，求获胜者序号，保证得分互不相等。
* **大体思路** ： 数据范围很小直接 **暴力** ，得分存到2n个set中，比较时胜者删去大于败者所有得分的最小得分即可。
```c++
#include <bits/stdc++.h>

using namespace std;

const int maxn = (1 << 14) + 5;
set<int> a[maxn];
set<int>::iterator p;
int n, len, res, x, ct;

void solve() {

    static int kase = 0;
    cin >> n;
    len = n, n = 1 << n;
    for (int i = 0; i < maxn; i++) a[i].clear();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < len; j++) cin >> x, a[i].insert(x);
    }
    while (len--) {
        bool flag = false;
        for (int i = 0, pre = 0; i < n; i++) {
            if (!a[i].empty()) {
                if (flag) {
                    if ((p = a[i].lower_bound(*a[pre].rbegin())) != a[i].end()) {
                        a[res = i].erase(p);
                        a[pre].clear();
                    } else if ((p = a[pre].lower_bound(*a[i].rbegin())) != a[pre].end()) {
                        a[res = pre].erase(p);
                        a[i].clear();
                    }
                } else pre = i;
                flag = !flag;
            }
        }
    }
    cout << "Case #" << ++kase << ": " << res + 1 << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> ct;
    while (ct--) solve();

    return 0;
}
```

## 6_C. Generation I （组合数学 + 逆元）
* **题目大意** ： 对n个空集操作n次，每次在`[i, n]`编号的集合里添加1个`[1, m]`范围内的数，问最后这n个集合的情况数。（论 **认真读题** 的重要性，题目一直看错导致样例怎么都想不通导致挂机）
* **大体思路** ： 观察到每个数字插入只有在第一个位置插入是有效的，后面插入这个数字等于没插；且两个不同的结果只可能因为选的数字不一样或者这些数字第一次插入位置不一样。设尾集合不重复数个数为k，由于每次操作只对后一个集合产生影响，故将重复的数视为整体，将n次操作划分为k个部分，由 **隔板法** 得到`c[n - 1][k - 1]`。而这k个部分是由m个数取出来任意排列的，所以要乘上`A[m][k]`，从而得到`res = c[n - 1][k - 1] * A[m][k]`。枚举`k ∈ [1, min(n, m)]`求和一下即可， **排列数** 和 **组合数** 每次可由前一项推得，还要预处理一下 **逆元表** 。
```c++
#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int maxn = int(1e6 + 5);
const int mod = 998244353;
LL ni[maxn];
LL n, m, sum, res;
int ct;

void solve() {

    static int kase = 0;
    cin >> n >> m;
    res = sum = m % mod;
    for (int i = 1; i < min(n, m); i++) {
        (sum *= (m - i) % mod * ((n - i) % mod) % mod * ni[i] % mod) %= mod;
        (res += sum) %= mod;
    }
    cout << "Case #" << ++kase << ": " << res << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    ni[1] = 1;
    for (int i = 2; i < maxn; i++) ni[i] = ni[mod % i] * (mod - mod / i) % mod;
    cin >> ct;
    while (ct--) solve();

    return 0;
}
```

## 6_D. Bulbasaur （贪心）
* **题目大意** ：n个人脸匹配m件衣服，脸能连多个衣服，衣服只能连1个脸。给定k条边，求最大边权和。
* **大体思路** ： 对每个衣服维护最大值，直接求和即可。
```c++
#include <bits/stdc++.h>

using namespace std;

const int maxn = int(1e5 + 5);
int a[maxn], ct;
int n, m, k, x, y, cost;
long long res;

void solve() {

    static int kase = 0;
    res = 0;
    cin >> n >> m >> k;
    fill(a, a + maxn, INT_MIN);
    for (int i = 0; i < k; i++) {
        cin >> x >> y >> cost;
        a[y] = max(a[y], cost);
    }
    for (int i = 1; i <= m; i++) res += (a[i] == INT_MIN) ? 0 : a[i];
    cout << "Case #" << ++kase << ": " << res << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> ct;
    while (ct--) solve();

    return 0;
}
```

## 6_I. Team Rocket
（占坑）

## 6_J. Heritage of skywalkert （随机化 + gcd）
* **题目大意** ： 给定n个由a, b, c生成的随机数，求2数lcm最大值。
* **大体思路** ： 随机生成函数没有规律可循，考虑到任意两个 **随机正整数** 互质的概率为 **6 / (pi ^ 2)**，不妨取前100大的数暴力一下lcm。 **快速排序** 时间复杂度为`O(nlogn)`刚好卡超时，可以用`nth_element(a, a + n - 100, a + n)`后100大的数，特判一下n是否大于100即可。
```c++
#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long LL;

const int maxn = int(1e7 + 5);
LL a[maxn], res;
unsigned x, y, z, t;
int n, m, ct;

inline LL lcm(LL x, LL y) {

    return x / __gcd(x, y) * y;
}
unsigned work() {

    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;
    t = x, x = y, y = z;
    return z = t ^ x ^ y;
}
void solve() {

    static int kase = 0;
    res = 0;
    cin >> n >> x >> y >> z;
    for (int i = 0; i < n; i++) a[i] = work();
    m = max(0, n - 100);
    nth_element(a, a + m, a + n);
    for (int i = m; i < n; i++) {
        for (int j = i + 1; j < n; j++) res = max(res, lcm(a[i], a[j]));
    }
    cout << "Case #" << ++kase << ": " << res << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> ct;
    while (ct--) solve();

    return 0;
}
```



