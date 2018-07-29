* [nowcoder contest 4](https://www.nowcoder.com/acm/contest/142#question)

## A. Ternary String
（占坑）

## D. Another Distinct Values (打表找规律 + 构造)
* **题目大意** ： 构造一个n*n的矩阵，只能填入`-1, 0, 1`，使得每行总和与每列总和的`2 * n`个数互不相同。
* **大体思路** ： dfs一下找规律，复杂度有点高只能打出前4个表。看了一下一般规律是以正对角线划分， **上三角矩阵** 都是-1， **下三角矩阵** 都是1，对角线一半是0， 一半是1。
```c++
#include <bits/stdc++.h>

using namespace std;

int n, ct;

void solve() {

    cin >> n;
    if (n % 2) {
        cout << "impossible" << endl;
        return;
    }
    cout << "possible" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (i == j ? (i < n / 2) : (i < j) ? -1 : 1) << " \n"[j == n - 1];
        }
    }
}
int main() {

    cin >> ct;
    while (ct--) solve();

    return 0;
}
```

## F. Beautiful Garden （模拟）
* **题目大意** : 在一个长宽都是偶数的字符矩阵中心覆盖一个矩阵，使其余部分上下左右都对称，求覆盖方案数。
* **大体思路** : 矩阵中所有不对称的点都要被覆盖掉，用`(x, y)`分别记录不对称点距离中心的最大横向距离和纵向距离，答案即为`(n - x) * (m - y) / 4`。由于覆盖的矩阵不能为空，特判一下当边长为0时改为2即可。

```c++
#include <bits/stdc++.h>

using namespace std;

const int maxn = 2005;
char a[maxn][maxn];
int n, m, ct;

void solve() {

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> a[i][j];

    int x = 0, y = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] != a[n + 1 - i][j]) x = max(x, 2 * abs(n / 2 - i));
            if (a[i][j] != a[i][m + 1 - j]) y = max(y, 2 * abs(m / 2 - j));
        }
    }
    if (!x) x = 2;
    if (!y) y = 2;
    cout << (n - x) * (m - y) / 4 << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> ct;
    while (ct--) solve();

    return 0;
}
```

## G. Maximum Mode (贪心 + 模拟)
* **题目大意** ： 给定n个数，求删除m个数后出现次数最多的数的最大值（最多次数不能相同）。
* **大体思路** ： 用2个map分别记录`(num， ct)`和`(ct, nums)`，其中num为数，ct为数出现次数。从最大的数开始贪心，所有出现次数（设为cm）大于等于该数出现次数（设为c）的数都至少要减去`cm - c + 1`才能使得该数出现次数最大，若减去的此处小于等于m则该数满足条件，否则往下一个大的数继续贪心。

```c++
#include <bits/stdc++.h>

using namespace std;

map<int, int> all;       //first -> num, second -> ct
map<int, set<int>> a;    //first -> ct, second -> nums
int n, m, ct, x;

void solve() {

    a.clear();
    all.clear();
    cin >> n >> m;
    while (n--) {
        cin >> x;
        all[x]++;
    }
    for (auto &p : all) a[p.second].insert(p.first);
    for (auto p = all.rbegin(); p != all.rend(); p++) {
        int res = p->first, ct = p->second, sum = 0;
        for (auto &k : a) {
            if (k.first >= ct) sum += (k.second.size() - (k.first == ct)) * (k.first - ct + 1);
        }
        if (sum <= m) {
            cout << res << endl;
            return;
        }
    }
    cout << -1 << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> ct;
    while (ct--) solve();

    return 0;
}
```







