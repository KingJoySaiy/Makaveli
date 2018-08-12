* [nowcoder contest 6](https://www.nowcoder.com/acm/contest/144#question)

## A. Singing Contest （模拟）
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

## C. Generation I （组合数学 + 逆元）
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

## D. Bulbasaur （贪心）
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
## I. Team Rocket
## J. Heritage of skywalkert （随机化 + gcd）
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



