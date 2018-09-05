* [nowcoder contest 9](https://www.nowcoder.com/acm/contest/147#question)
* [nowcoder contest 10](https://www.nowcoder.com/acm/contest/148#question)
## 9_A. Circulant Matrix

## 9_E. Music Game （概率 + 期望）
* **题目大意** ： 给定n个数，表示第i次答对概率为`a[i] / 100`，连续答对k次得分`k ^ m`，问总得分的期望。
* **大体思路** ： 可以对每段的期望求和，而不必考虑总的答题情况。设`p(i, j)`表示ij闭区间内都连对的概率，则`p(i, j) = sigma{k = i : j}{a[i] / 100}`。设`f(i, j)`表示i，j位置答错（或为边界），而在其开区间内连对的概率，则`f(i, j) = (100 - a[i]) / 100 * (100 - a[j]) / 100 * p(i + 1, j - 1)`，对每个f再乘上得分值即可。
```c++
#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int mod = int(1e9 + 7);
const int maxn = 1005;
const int ni = 570000004;
LL a[maxn][maxn], score[maxn];
LL x, good[maxn], bad[maxn], res;
int n, m;

LL mod_pow(LL x, LL n) {

    LL res = 1;
    while (n) {
        if (n % 2) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(), cout.tie();
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        good[i] = x * ni % mod;
        bad[i] = (100 - x) * ni % mod;
        score[i] = mod_pow(i, m);
    }
    bad[0] = bad[n + 1] = 1;
    for (int i = 1; i <= n; i++) {
        a[i][i] = good[i];
        for (int j = i + 1; j <= n; j++) a[i][j] = a[i][j - 1] * good[j] % mod;
    }
    for (int i = 0; i <= n; i++) {
        for (int j = i + 2; j < n + 2; j++) {
            (res += bad[i] * bad[j] % mod * a[i + 1][j - 1] % mod * score[j - i - 1] % mod) %= mod;
        }
    }
    cout << (res + mod) % mod << endl;

    return 0;
}
```

## 9_F. Typing practice

## 9_H. Prefix Sum

## 10_A. Rikka with Lowbit

## 10_D. Rikka with Prefix Sum

## 10_F. Rikka with Line Graph

## 10_J. Rikka with Nickname （大模拟 + 二分）
* **题目大意** ：给定n个字符串进行拼接，从第二个开始去掉最长前缀拼在已有串后面，满足前缀是已有串的子串。
* **大体思路** ： 由于只含小写英文字母，故想到用`id[26][maxn]`存储每个字母再已有串中的所有下标。依次处理每个串的每个 **前缀字符** ，不断 **二分** 该字符出现的下标now，并更新now。当找不到比now大的下标或到达串尾则结束，输出最终串即可。
```c++
#include <bits/stdc++.h>

using namespace std;

const int maxn = int(1e6 + 5);
char res[maxn], s[maxn];
int id[26][maxn], l[26];
int n, m, p, len, ct;

void work() {

    len = strlen(s);
    long now = -1, t, c;
    for (p = 0; p < len; p++) {
        c = s[p] - 'a';
        if ((t = lower_bound(id[c], id[c] + l[c], now + 1) - id[c]) != l[c]) now = id[c][t];
        else return;
    }
}
void solve() {

    cin >> m >> res;
    n = strlen(res);
    memset(l, 0, sizeof(l));
    for (int i = 0; i < n; i++) id[res[i] - 'a'][l[res[i] - 'a']++] = i;
    while (--m) {
        cin >> s;
        work();
        for (int i = p; i < len; i++) {
            id[s[i] - 'a'][l[s[i] - 'a']++] = n;
            res[n++] = s[i];
        }
    }
    res[n] = '\0';
    cout << res << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(), cout.tie();
    cin >> ct;
    while (ct--) solve();

    return 0;
}
```


