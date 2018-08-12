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

## C. Generation I
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
## J. Heritage of skywalkert



