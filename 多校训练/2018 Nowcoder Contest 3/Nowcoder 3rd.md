* [nowcoder contest 3](https://www.nowcoder.com/acm/contest/141#question)

## A. PACM Team （背包 + 路径）
* **题目大意** ：有n组人，每组有`p, a, c, m`个人分别负责4个领域，其能力值为g。在4个领域不超过`P, A, C, M`情况下总能力值尽量大，输出选组序号。
* **大体思路** : 01背包问题，想到用五维dp。`dp[t][i][j][k][l] = max(dp[t - 1][i][j][k][l], dp[t - 1][i - p[t]][j - a[t]][k - c[t]][l - m[t]] + g[t])`，在递推是可以省去第一维度降到4维dp。然后要输出序列可以用五维布尔数组标记，逆序判断是否为`true`，若是则记录序号并减去4个属性值，继续往前找，否则直接忽略即可。

```c++
#include <bits/stdc++.h>

using namespace std;

const int maxn = 37;
short p[maxn], a[maxn], c[maxn], m[maxn], g[maxn];
short P, A, C, M, n;
bool book[maxn][maxn][maxn][maxn][maxn];
short dp[maxn][maxn][maxn][maxn];   //分别选了i, j, k, l个人的最大能力值
vector<int> res;

int main() {

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> p[i] >> a[i] >> c[i] >> m[i] >> g[i];
    cin >> P >> A >> C >> M;

    for (int t = 0; t < n; t++) {
        for (int i = P; i >= p[t]; i--)
            for (int j = A; j >= a[t]; j--)
                for (int k = C; k >= c[t]; k--)
                    for (int l = M; l >= m[t]; l--) {
                        if (dp[i][j][k][l] >  dp[i - p[t]][j - a[t]][k - c[t]][l - m[t]] + g[t]) continue;
                        dp[i][j][k][l] = dp[i - p[t]][j - a[t]][k - c[t]][l - m[t]] + g[t];
                        book[t][i][j][k][l] = true;
                    }
    }
    while (n--) {       //逆序求选的索引
        if (book[n][P][A][C][M]) {
            P -= p[n];
            A -= a[n];
            C -= c[n];
            M -= m[n];
            res.push_back(n);
        }
    }
    cout << res.size() << endl;
    for (auto &p : res) cout << p << ' ';

    return 0;
}
```

## E.	Sort String （kmp / hash / 思维 + 暴力）
* **题目大意** ： 给定一个字符串环，每次将首字符移到末尾，构成n个字符串。相同的分为一组，输出组数和每组的首字符编号。
* **大体思路** ： 两字符串相同意味着该字符串有 **循环子串** ，且2个首字符在循环子串中的相同位置。所以分组书就是最大循环子串长度，每组字符串个数即为循环子串出现次数`ct = len / l`，其中len为总串长，l为循环子串长度，前提是`len % l == 0`，而每组的好即为每个循环子串对应位置索引的集合。

```c++
#include <bits/stdc++.h>

using namespace std;

const int maxn = int(1e6 + 5);
char s[maxn];
int len;

int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> s;
    len = strlen(s);

    for (int l = 1, ct; l <= len; l++) {        //枚举子串长度
        if (len % l) continue;
        ct = len / l;
        for (int i = 0; i < l; i++) {
            for (int j = 1; j < ct; j++) {
                if (s[j * l + i] != s[i]) goto ed;  //有一个对应字符不匹配则结束
            }
        }

        cout << l << endl;
        for (int i = 0; i < l; i++) {
            cout << ct << ' ';
            for (int j = 0, t = i - l; j < ct; j++)
                cout << (t += l) << " \n"[j == ct - 1];
        }
        return 0;

        ed: continue;
    }

    return 0;
}
```

## H. Diff-prime Pairs （gcd + 素数筛）
* **题目大意** ： 给定n，问多少小于等于n的数对`(i, j)`满足`i / gcd(i, j)`和` j / gcd(i, j)`都是素数。
* **大体思路** ： i和j肯定不等，因为若相等则除gcd后值为1，1不是素数，所以答案肯定是偶数。考虑`i < j`即可，设2个素数为x和y，则gcd可以是任意值，只要`x * gcd = i ≤ n`且`y * gcd = j ≤ n`即可，问题转换为求小于等于n的 **素数整数倍的数对** 个数，素数整数倍个数显然是`n / prime`，顺便乘以前面素数的个数即可，因为若大素数的整数倍小于等于n，小的素数也满足。
```c++
#include <bits/stdc++.h>
using namespace std;

const int maxn = int(1e7 + 5);
bool b[maxn];
long long res, n, t;

int main() {

    cin >> n;
    for (int i = 2; i <= n; i++) {
        if (!b[i]) {
            res += n / i * 2 * t++;
            for (int j = i + i; j <= n; j += i) b[j] = true;
        }
    }
    cout << res << endl;

    return 0;
}
```

## J. Distance to Work
* **题目大意** ： 给定简单多边形各个顶点和圆心坐标, 多边形面积为s2, 圆面积为s1, 求圆半径使之满足`(s2 - s1) / s2 = p / q`。
* **大体思路** ： 易知`s1 = s2 * (1 - p / q)`, 二分圆的半径, 套用多边形与圆面积交的模板即可。（实践证明kuang斌的计算几何模板只能过样例=_=）
```c++
#include<bits/stdc++.h>

using namespace std;
const double pi = acos(-1);
const int maxn = 205;
const double eps = 1e-12;

struct Point {

    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator + (const Point &b) const {       //向量+向量
        return Point(x + b.x, y + b.y);
    }
    Point operator - (const Point &b) const {        //向量-向量 or 点-点
        return Point(x - b.x, y - b.y);
    }
    double operator ^ (const Point &b) const {       //向量的叉积
        return x * b.y - y * b.x;
    }
    double operator * (const Point &b) const {       //向量的点积
        return x * b.x + y * b.y;
    }
    Point operator * (const double t) const {        //向量乘浮点数
        return Point(t * x, t * y);
    }
    Point operator / (const double &t) const {       //向量除以浮点数
        return Point(x / t, y / t);
    }
    double dis(Point &t) {  //返回2点之间距离
        return hypot(x - t.x, y - t.y);
    }
} a[maxn];

int n, m;
double x, y, p, q;
double s2;

inline double dis2(Point A, Point B) { 

    return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y); 
}
double DisLine(Point P, Point A, Point B) {       //点P到直线AB距离

    return fabs((B - A) ^ (P - A)) / A.dis(B);
}
Point minPoint(Point P, Point s, Point e) {     //点到直线最近的点

    Point v = e - s;
    return s + v * (((P - s) * v) / (v * v));
}
double cal(Point A, Point B, Point P, double R) {

    double h = DisLine(P, A, B);
    if (dis2(P, A) <= R * R and dis2(P, B) <= R * R) return fabs((A - P) ^ (B - P)) / 2;//A B两点均在圆内
    if (dis2(P, A) > R * R)swap(A, B);
    if (dis2(P, A) <= R * R and dis2(P, B) > R * R) {                               //A B两点有一点在圆内
        double ang = (dis2(P, A) + dis2(A, B) - dis2(P, B)) / (2 * A.dis(P) * A.dis(B));
        ang = acos(ang);
        double C = ang + asin(sin(ang) * P.dis(A) / R);
        double len = sin(C) * R / sin(ang);
        ang = (dis2(P, A) + dis2(P, B) - dis2(A, B)) / (2 * P.dis(A) * P.dis(B));
        ang = acos(ang) - (pi - C);
        return len * h / 2 + ang * R * R / 2;
    }
    double ang = (dis2(P, A) + dis2(P, B) - dis2(A, B)) / (2 * P.dis(A) * P.dis(B));    //A B两点均在圆外
    double area = acos(ang) * R * R / 2;
    Point PP = minPoint(P, A, B);
    if (h >= R or ((PP - P) ^ (A - P)) * ((PP - P) ^ (B - P)) > 0)return area;            //线段AB与圆不相交
    return area - (2 * acos(h / R) * R * R / 2 - h * sqrt(R * R - h * h));                //线段AB与圆相交
}
void solve() {

    scanf("%lf%lf%lf%lf", &x, &y, &p, &q);
    Point pp(x, y);
    double l = 0, r = 1e9, m, s1, ss = s2 * (1 - p / q);
    while (fabs(r - l) > eps) {
        m = (l + r) / 2;
        s1 = 0;
        for (int i = 0; i < n; i++) {
            if (((a[i] - pp) ^ (a[(i + 1) % n] - pp)) == 0) continue;
            double area = cal(a[i], a[(i + 1) % n], pp, m);
            if (((a[i] - pp) ^ (a[(i + 1) % n] - pp)) > 0) s1 += area;
            else s1 -= area;
        }
        s1 = fabs(s1);
        if (s1 < ss) l = m;
        else r = m;
    }
    printf("%.8f\n", l);
}
int main() {

    cin >> n;
    for (int i = 0; i < n; i++) scanf("%lf%lf", &a[i].x, &a[i].y);
    for (int i = 0; i < n; i++) s2 += a[i] ^ (a[(i + 1) % n]);
    s2 = fabs(s2) / 2;
    cin >> m;
    while (m--) solve();

    return 0;
}
```




