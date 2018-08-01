* [Multi-University contest 4](http://acm.hdu.edu.cn/userloginex.php?cid=805)

## 1002. Harvest of Apples （组合数学 + 莫队分块）
（占坑）

## 1004. Nothing is Impossible （贪心出锅了）
* **题目大意** : （出锅导致修改题面与数据）给定若干题，每题1个正确选项`a[i]`错误选项。m个同学做题，问过题最多的人至少过了几题。
* **大体思路** : 尽量先做错误选项少的，每次剩下`a[i] + 1`分之一的题答对，所以只要m大于0，就一直出下去并让答案加一。

```c++
#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
#define int LL

const int maxn = int(1e5 + 5);
int a[maxn], x;
int n, m, ct;

void solve() {

    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> x >> a[i];
    sort(a, a + n);

    LL res = 1;
    for (int i = 0; i < n; i++) {
        if (m / (res *= (a[i] + 1)) == 0) {
            cout << i << endl;
            return;
        }
    }
    cout << n << endl;
}
int32_t main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    for (cin >> ct; ct; ct--) solve();

    return 0;
}
```

## 1005. Matrix from Arrays
（占坑）

## 1010. Let Sudoku Rotate （数独 + 暴搜剪枝）
（占坑）

## 1011. Expression in Memories （大模拟）
* **题目大意** ： 给定一个可能不完整的加法乘法表达式，要求填完整使之合法。
* **大体思路** ： 前缀0后的?改为+，其他?都改为1，然后判断是否有两个运算符靠在一起，首尾必须是是数字。

```c++
#include <bits/stdc++.h>

using namespace std;

const int maxn = int(1e5 + 5);
char a[maxn];
int n, ct;

bool check() {

    for (int i = 1; i < n; i++) {
        if (a[i] == '0' and !isdigit(a[i - 1]) and isdigit(a[i + 1])) return false;
        if (!isdigit(a[i]) and !isdigit(a[i + 1])) return false;
    }
    return isdigit(a[1]) and isdigit(a[n]);
}
void solve() {

    cin >> a + 1;
    n = strlen(a + 1);
    for (int i = 1; i <= n; i++) {
        if (a[i] == '0' and !isdigit(a[i - 1]) and a[i + 1] == '?') a[i + 1] = '+';
        else if (a[i] == '?') a[i] = '1';
    }
    cout << (check() ? (a + 1) : "IMPOSSIBLE") << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    for (cin >> ct; ct; ct--) solve();

    return 0;
}
```

## 1012. Graph Theory Homework （贪心）
* **题目大意** ： 给定节点权值，节点之间花费为`floor(sqrt(abs(v1 - v2)))`，问从1到n的最小花费。
* **大体思路** ： 边权满足三角不等式，所以直接求节点1到节点n的花费最小。

```c++
#include <bits/stdc++.h>

using namespace std;
int n, ct, a, b;

void solve() {

    cin >> n >> a;
    for (int i = 1; i < n; i++) cin >> b;
    cout << int(sqrt(abs(a - (n == 1 ? a : b)))) << endl;
}
int main() {

    for (cin >> ct; ct; ct--) solve();

    return 0;
}
```