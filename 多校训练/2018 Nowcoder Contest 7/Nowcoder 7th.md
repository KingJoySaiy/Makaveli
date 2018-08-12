* [nowcoder contest 7](https://www.nowcoder.com/acm/contest/145#question)

## A. Minimum Cost Perfect Matching（找规律 + 暴力）
* **题目大意** ： 构造`[0, n)`的n个数，满足`sigma(i ^ a[i])`最小。
* **大体思路** ： 打表找规律，观察到构造的 **异或和** 最小都是0，意味着每一位异或值都是0。然后观察到 **降序枚举** 比升序枚举快，直接暴力模拟一下即可。
```c++
#include <bits/stdc++.h>

using namespace std;

const int maxn = int(5e5 + 5);
int res[maxn], n, id;

int main() {

    cin >> n;
    memset(res, -1, sizeof(res));
    for (int k = n - 1; ~k; k--) {
        while (true) {
            if (res[id] == -1 and !(id & k)) break;
            id = (id + 1) % n;
        }
        res[id] = k;
    }
    for (int i = 0; i < n; i++) cout << res[i] << " \n"[i == n - 1];

    return 0;
}
```

## C. Bit Compression（暴力 + 剪枝）
* **题目大意** ： 给定长度为`2 ^ n`的01串，执行n次相邻2位取`& | ^`三种逻辑运算，求最后为串为1的方案数。
* **大体思路** ：（ **折半搜索** 很尴尬的T了）看到一种很好的做法是开一个 **二维数组** 或 **unordered_map** 记录处理后的字符串以及出现次数，将维护的出现次数每次叠加，最后输出长度为1且串为1的记录点即可。
```c++
#include<bits/stdc++.h>

using namespace std;

unordered_map<string, int> a[20];
string s;
int len, n;

int main() {

    cin >> n >> s;
    for (auto &p : s) p -= '0';
    a[n][s] = 1;
    while (n--) {
        for (auto p : a[n + 1]) {
            s = p.first;
            len = 1 << (n + 1);
            string t[3];
            for (int i = 0; i < len; i += 2) {
                t[0] += s[i] & s[i + 1];
                t[1] += s[i] | s[i + 1];
                t[2] += s[i] ^ s[i + 1];
            }
            for (int i = 0; i < 3; i++) a[n][t[i]] += p.second;
        }
    }
    cout << a[0][string(1, 1)] << endl;

    return 0;
}
```

## E. Counting 4-Cliques
（占坑）

## J. Sudoku Subrectangles
（占坑）


