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

## G. transform （二分 + 尺取法）
* **题目大意** ：坐标轴上有若干箱子，每个箱子里有若干个货物，移动1个货物的费用是距离差的绝对值。问在最大花费为T，最多能集中到一起的货物数量。
* **大体思路** ：维护前i个货物的数量前缀和`ct[i]`，把前i个货物移动到坐标原点的花费`cost[i]`，每个箱子的位置为`dis[i]`。易知将`[l, r]`所有货物全部移动到l的花费为`costL = cost[r] - cost[l - 1] - dis[l] * (ct[r] - ct[l - 1])`，表示把区间所有货物移到坐标0，再减去移多的长度`dis[l]`。而将`[l, r]`所有货物移动到r的花费为`costR = (ct[r] - ct[l - 1]) * (dis[r] - dis[l - 1]) - costL(l, r)`，表示把区间内的所有货物整体向右移动`(r - l)`，从而区间变为`[r, 2 * r - l]`，再根据上式全部移动到区间最左端r即可。答案货物数量一定是升序的，可以二分答案。一个贪心的思想是将某区间`[l, r]`的货物尽量移动到其 **中位数** 附近，对于每个二人枚举的答案，利用 **尺取法** （或称 **滑窗** ）得到满足条件的区间`[l, r]`，实际上只从左往右滑窗不一定能滑到最右端，所以需要2次滑窗。再利用上述2个式子判断`[l, mid]`的货物移到`mid`和`[mid, r]`的货物移到`mid`的花费总和是否小于T即可，其中`mid`表示区间的中位数。实现起来有很多细节问题，比较难处理。

```c++
#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int maxn = int(5e5 + 5);
LL dis[maxn], ct[maxn], cost[maxn], all, n;

LL costL(LL l, LL r) {

    return cost[r] - cost[l - 1] - dis[l] * (ct[r] - ct[l - 1]);
}
LL costR(LL l, LL r) {

    return (ct[r] - ct[l - 1]) * (dis[r] - dis[l]) - costL(l, r);
}
bool check(LL x) {

    LL l, r, m, mid = x / 2 + 1;     //中位数
    l = r = m = 1;
    while (true) {
        while (r <= n and ct[r] - ct[l - 1] < x) r++;
        while (m <= n and ct[m] - ct[l - 1] < mid) m++;
        if (r > n or m > r) break;
        if (costR(l, m) + costL(m, r) - (dis[r] - dis[m]) * (ct[r] - ct[l - 1] - x) <= all) return true;
        l++;
    }
    l = r = m = n;
    while (true) {
        while (l >= 1 and ct[r] - ct[l - 1] < x) l--;
        while (m >= 2 and ct[r] - ct[m - 1] < mid) m--;
        if (l < 1 or m < l) break;
        if (costR(l, m) + costL(m, r) - (dis[m] - dis[l]) * (ct[r] - ct[l - 1] - x) <= all) return true;
        r--;
    }
    return false;
}

int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> all, all /= 2;
    for (int i = 1; i <= n; i++) cin >> dis[i];
    for (int i = 1; i <= n; i++) {
        cin >> ct[i];
        cost[i] = cost[i - 1] + dis[i] * ct[i];
        ct[i] += ct[i - 1];
    }
    LL l = -1, r = ct[n] + 1, m;
    while (r - l > 1) {
        m = (l + r) / 2;
        if (check(m)) l = m;
        else r = m;
    }
    cout << l << endl;

    return 0;
}
```

## I. car （模拟）

* **题目大意** ：在n*n的方格中右m个障碍，从角落放车以相同速度行驶（中途不能相撞），问最多能放的小车数目。
* **大体思路** ：先考虑没有障碍，为了让小车不相撞，四条边上分别放`n / 2`辆车，这样最多能放`2 * n`辆，但是n为奇数时在`2 / n`行或列上放2辆速度相同的车会导致相撞，故只能放1辆，从而答案为`res = 2 * n - n % 2`。如果有障碍，则用2个长度为n的布尔数组标记一下即可。

```c++
#include <bits/stdc++.h>

using namespace std;

const int maxn = int(1e5 + 5);
int a[maxn], b[maxn];
int n, m, x, y;

int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    while (m--) {
        cin >> x >> y;
        a[x - 1] = b[y - 1] = true;
    }

    int res = 2 * n;
    for (int i = 0; i < n; i++) res -= a[i] + b[i];
    if (n % 2 and !a[n / 2] and !b[n / 2]) res--;
    cout << res << endl;

    return 0;
}
```

## J. farm （随机化 / 二维线段树 / 大模拟）

* **题目大意** ：给定n*m个数，t次修改把`(x1, y1)(x2, y2)`为对角线的矩阵内所有数改为k，问最后与初始数不同的个数。
* **大体思路** ：大致三种解题思路 **随机化** , **二维线段树** , **大模拟**。第三者更容易理解和实现，每个数最大`1e6`所以分别维护每个数前21位的 **矩阵前缀和** ，问题转换成01问题，数字不改变当且仅当所有二进制位都不改变。根据矩阵前缀和可以快速求出`(i, j)`位置处第ct位0或1变化次数，若有一个改变则该位置的数字坏掉。开一个布尔数组标记，最后坏掉的数求和一下即可。
```c++
#include <iostream>
#include <cstring>

using namespace std;

const int maxn = int(2e6 + 5);
int a[maxn], num[2][maxn];
int x1[maxn], y1[maxn], x2[maxn], y2[maxn], k[maxn];
bool bad[maxn];
int n, m, t, res;

bool find(int x, int ct) {  //x二进制下从右往左第ct位

    while (--ct) x >>= 1;
    return bool(x % 2);
}
void work() {

    for (int ct = 1, id; ct < 22; ct++) {   //1e6维护二进制下21位即可
        memset(num, 0, sizeof(num));
        for (int i = 0; i < t; i++) {       //更新前缀和
            id = find(k[i], ct);
            num[id][(x2[i] + 1) * m + y2[i] + 1]++;
            num[id][x1[i] * m + y1[i]]++;
            num[id][(x2[i] + 1) * m + y1[i]]--;
            num[id][x1[i] * m + y2[i] + 1]--;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int _0 = 0, _1 = 0;
                find(a[i * m + j], ct) ? (_1++) : (_0++);   //第ct位0和1出现个数
                num[0][i * m + j] += num[0][(i - 1) * m + j] + num[0][i * m + j - 1] - num[0][(i - 1) * m + j - 1];
                num[1][i * m + j] += num[1][(i - 1) * m + j] + num[1][i * m + j - 1] - num[1][(i - 1) * m + j - 1];
                _0 += num[0][i * m + j], _1 += num[1][i * m + j];
                bad[i * m + j] |= (_0 > 0 and _1 > 0);      //0或1有一个改变则坏掉
            }
        }
    }
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> t;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> a[i * m + j];

    for (int i = 0; i < t; i++)
        cin >> x1[i] >> y1[i] >> x2[i] >> y2[i] >> k[i];

    work();
    for (int i = 0; i < maxn; i++) res += bad[i];
    cout << res << endl;

    return 0;
}
```