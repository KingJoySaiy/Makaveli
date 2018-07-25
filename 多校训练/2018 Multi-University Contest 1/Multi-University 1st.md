* [Multi-University contest 1](http://acm.hdu.edu.cn/userloginex.php?cid=802)
## 1001. Maximum Multiple （打表找规律）
* **题目大意** ： 给定n，求n的3个因子乘积最大值，满足3个因子的和为n。
* **大体思路** ： 只知道这三个因子要尽量接近`n / 3`，没想太多直接打表找规律了。结论是： 若n是3的倍数则`n ^ 3 / 27`，若是4的倍数则`n ^ 3 / 32`，否则不存在。
```c++
#include <bits/stdc++.h>

using namespace std;
long long n, ct;

int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> ct;
    while (ct--) {
        cin >> n;
        cout << (n % 3 ? (n % 4 ? -1 : (n * n * n / 32)) : (n * n * n / 27)) << endl;
    }

    return 0;
}
```

## 1002. Balanced Sequence （排序 + 贪心）

## 1003. Triangle Partition （计算几何）
* **题目大意** ： 给定3n个点的坐标，保证三点不共线，求如何构建n个不相交的三角形。
* **大体思路** ： 因为三点不共线，按坐标升序排序，每次输出3个索引即可。
```c++
#include <bits/stdc++.h>

using namespace std;

struct ppp {

    int x, y, id;
    bool operator < (const ppp &t) const {
        return x < t.x or x == t.x and y < t.y;
    }
} a[3005];
int ct, n, m;

void solve() {

    cin >> n;
    m = 3 * n;
    for (int i = 0; i < m; i++) {
        cin >> a[i].x >> a[i].y;
        a[i].id = i + 1;
    }
    sort(a, a + m);
    for (int i = 0; i < m; i += 3) {
        cout << a[i].id << ' ' << a[i + 1].id << ' ' << a[i + 2].id << endl;
    }
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> ct;
    while (ct--) solve();

    return 0;
}
```

## 1004. Distinct Values （贪心）
* **题目大意** ： 构造长度为n的字典序最小序列，条件是m个`[l, r]`区间内不能有重复数字。
* **大体思路** ： 典型贪心题，要字典序最小则每次填入尽量小的数。记录每个位置最前的不能重复的索引，用set维护能填入的最小数，每次将这个区间前面的已填好的较小数添进set，每次填入set中最小数并从set中删除即可。
```c++
#include <bits/stdc++.h>

using namespace std;

const int maxn = int(1e5 + 5);

set<int> all;
int pre[maxn], res[maxn];
int n, m, ct, l, r;

void solve() {

    all.clear();
    cin >> n >> m;
    for (int i = 0; i < n; i++) all.insert(i + 1), pre[i] = i;
    while (m--) {
        cin >> l >> r;
        pre[r - 1] = min(pre[r - 1], l - 1);
    }
    for (int i = n - 1; i; i--) pre[i - 1] = min(pre[i - 1], pre[i]);

    for (int i = 0, t = 0; i < n; i++) {
        while (t < pre[i]) all.insert(res[t++]);
        res[i] = *all.begin();
        all.erase(res[i]);
    }
    for (int i = 0; i < n - 1; i++) cout << res[i] << ' ';
    cout << res[n - 1] << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> ct;
    while (ct--) solve();

    return 0;
}
```

## 1007. Chiaki Sequence Revisited （打表找规律）

## 1011. Time Zone （模拟）
* **题目大意** ： 给定24时制时间和时区，求东八区时间。
* **大体思路** ： 确定时区符号，小时转分钟，特判负数，前缀0，浮点数+0.1，这些都注意到就好了。
```c++
#include <bits/stdc++.h>

using namespace std;

const int mod = 1440;
int ct, a, b, res, sign;
char x[50];

void solve() {

    scanf("%d%d%s", &a, &b, x);
    sign = x[3] == '+' ? 1 : -1;
    res = (6 * sign * int(10 * atof(x + 4) + 0.1) + a * 60 + b - 480 + mod) % mod;
    printf("%02d:%02d\n", res / 60, res % 60);
}
int main() {

    cin >> ct;
    while (ct--) solve();

    return 0;
}
```
