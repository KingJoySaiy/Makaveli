* [Multi-University contest 3](http://acm.hdu.edu.cn/userloginex.php?cid=804)

## 1001. Ascending Rating
（占坑）

## 1004. Euler Function (欧拉函数 + 打表找规律)
* **题目大意** ： 对于 **欧拉函数** `φ(n) = x`，若x是和数则将n添到序列中，求序列中第k个数。
* **大体思路** ：打出欧拉函数表，对每个值进行素数判断打出序列表，发现序列是`5, 8, 9, 10, 11, 12...`，大胆猜测第一个数为5其余数都是`k + 5`。

```c++
#include <bits/stdc++.h>
using namespace std;
int n, ct;

int main() {

    cin >> ct;
    while (ct--) {
        scanf("%d", &n);
        printf("%d\n", n == 1 ? 5 : n + 5);
    }
    
    return 0;
}
```

## 1006. Grab The Tree （线性积）
（占坑）


## 1012. Visual Cube （大模拟）
* **题目大意** ： 给定立方体的长宽高，画出3D视图。
* **大体思路** ： 正面，上底面，右侧面分别看规律改字符即可。

```c++
#include <bits/stdc++.h>

using namespace std;

const int maxn = 200;
int n, m, a, b, c, ct;
char res[maxn][maxn];

int main() {

    cin >> ct;
    while (ct--) {
        cin >> a >> b >> c;
        n = 2 * b + 2 * c + 1, m = 2 * a + 2 * b + 1;
        for (int i = 0; i < maxn; i++) {
            for (int j = 0; j < maxn; j++) {
                res[i][j] = '.';
            }
        }
        for (int i = 2 * b; i < n; i++) {
            if (i % 2 == 0) {
                for (int j = 0; j < 2 * a + 1; j++) res[i][j] = ((j % 2) ? '-' : '+');
            } else {
                for (int j = 0; j < 2 * a + 1; j += 2) res[i][j] = '|';
            }
        }
        for (int i = 0; i < 2 * b + 1; i++) {
            int st = 2 * b - i, ed = m - i;
            if (i % 2 == 0) {
                for (int j = st; j < ed; j++) res[i][j] = ((j % 2) ? '-' : '+');
            } else {
                for (int j = st; j < ed; j += 2) res[i][j] = '/';
            }
        }
        for (int j = m - 1; j >= m - 2 * b; j--) {
            int st = m - j, ed = m - j + 2 * c;
            if (j % 2 == 0) {
                for (int i = st; i < ed; i++) res[i][j] = ((i % 2) ? '|' : '+');
            } else {
                for (int i = st + 1; i < ed; i += 2) res[i][j] = '/';
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) cout << res[i][j];
            cout << endl;
        }
    }

    return 0;
}
```
