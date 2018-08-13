* [Multi-University contest 5](http://acm.hdu.edu.cn/userloginex.php?cid=806)

## 1002. Beautiful Now

## 1005. Everything Has Changed （平面几何 / 解析几何）
* **题目大意** ： 给定圆心位于圆点的大园，和若干不内含大圆且互不相交的小圆，求大圆与校园相交的如下红色弧的长度。

<img src="_image/1005_1.jpg" width="240" height="200" />

* **大体思路** ： 所求弧长即为大圆周长减去大圆每个被小圆涵盖的弧长再加上每个小圆被大圆涵盖的弧长，其中2圆必须相交或相切。可以从 **平面几何** 和 **解析几何** 两个方向解题，但是后者计算量太大故只推荐前者。针对2圆构造如下 **辅助线** ：

<img src="_image/1005_2.jpg" width="240" height="200" />

* 易知对于相交两圆答案更新值为`res += θ2 * r - θ1 * R `，只要求到两个 **圆心角** 即可。根据 **余弦定理** 得到`cos(θ1 / 2) = (R^2 + o1o2^2 - r^2) / (2 * R * o1o2)`，同理`cos(θ2 / 2) = (r^2 + o1o2^2 - R^2) / (2 * r * o1o2)`，再利用 **反余弦函数** 即可求到2个 **圆心角** 。每次判断是否相交或相切，更新答案即可。

```c++
#include<bits/stdc++.h>

using namespace std;

const double pi = acos(-1);
int n, m, ct, x, y, r;

inline double hypot2 (double x, double y) {
    return x * x + y * y;
}
void solve() {

    cin >> n >> m;
    double res = 2 * pi * m, s1, s2;
    while (n--) {
        cin >> x >> y >> r;
        if (hypot(x, y) < m - r or hypot(x, y) > m + r) continue;
        s1 = 2 * acos((m * m + hypot2(x, y) - r * r) / (2 * m * hypot(x, y)));
        s2 = 2 * acos((r * r + hypot2(x, y) - m * m) / (2 * r * hypot(x, y)));
        res += r * s2 - m * s1;
    }
    printf("%.8f\n", res);
}
int main() {

    cin >> ct;
    while (ct--) solve();

    return 0;
}
```

## 1007. Glad You Came

## 1008. Hills And Valleys