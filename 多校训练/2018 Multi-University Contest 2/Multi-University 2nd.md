* [Multi-University contest 2](http://acm.hdu.edu.cn/userloginex.php?cid=803)
## 1004. Game （博弈论 / 规律）
* **题目大意** ： 2人删除从`1~n`的数字，每次删一个数并删除其所有因子，2人都采取最优策略，问先手是赢是输。
* **大体思路** ： 这题先手要么必胜要么必输，因为1是任何数的因子，先删其他任何数都将把1删掉。假设后手必胜，那么先手只需先把1删掉即可变成先手必胜。其实打出20个表发现全是`Yes`也应该大胆猜一下先手稳赢。

```c++
#include <bits/stdc++.h>

int main() {
    
    for (int n; std::cin >> n; puts("Yes"));
    
    return 0;
}
```

## 1005. Hack It （数论 + 构造）
* **题目大意** ： 构造一个n*n`(1 ≤ n ≤ 2000)`的01方阵，要求1个数大于85000且任意子矩阵4个对角不能都为1。
* **大体思路** ： 一种数论构造方法是先让1尽量出现在同一列，再在之后每一列保证每一列只出现1次，例如`n = 5`如下所示：
```
10000 01000 00100 00010 00001 
10000 00100 00001 01000 00010 
10000 00010 01000 00001 00100 
10000 00001 00010 00100 01000 
10000 10000 10000 10000 10000

01000 00100 00010 00001 10000 
01000 00010 10000 00100 00001 
01000 00001 00100 10000 00010 
01000 10000 00001 00010 00100 
01000 01000 01000 01000 01000 
...
```

* 这样构成了一个`n * (n * n)`的矩阵，考虑将都矩阵中的5个小方阵向右移动一列，即列序号加1取模。这样就构成不一样的新矩阵（如上图），同理构造剩余矩阵即可满足条件。因为涉及到取模运算，方阵中每个小方阵都唯一的充要条件是n是素数。尝试多个素数后发现`n = 47`时能让`2000 * 2000`的方阵中1的次数为`85105`满足题意。

```c++
#include<bits/stdc++.h>

using namespace std;

const int maxn = 2500;
int a[maxn][maxn], n = 47, m = n * n, res = 2000;

int main() {

    ios::sync_with_stdio(false), cin.tie(), cout.tie();

    cout << res << endl;
    for (int k = 0; k < m; k++) {
        for (int i = 0; i < n; i++) {
            a[k][i * n + ((k % n + 1) * i + k / n) % n] = 1;
        }
    }
    for (int i = 0; i < res; i++) {
        for (int j = 0; j < res; j++) {
            cout << a[i][j];
        } cout << endl;
    }

    return 0;
}
```

## 1006. Matrix
（占坑）

## 1010. Swaps and Inversions （树状数组 / 逆序数）
* **题目大意** ： 每次支付x或y交换相邻两数使数组升序，求最小支付多少。
* **大体思路** ： 显然交换顺序与结果无关，只需求出逆序数为res，答案即为`res * min(x, y)`，在归并排序时顺便求一下逆序数即可。

```c++
#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

const int maxn = int(1e5 + 7);
int a[maxn], b[maxn], num[maxn];
int n, x, y;
LL res;

void Merge(int l, int m, int r) {

    int id1 = 0, id2 = 0;
    int n1 = 0, n2 = 0;
    for (int i = l; i < m; i++) a[n1++] = num[i];
    for (int i = m; i < r; i++) b[n2++] = num[i];

    for (int i = l; i < r; i++) {
        if (id1 == n1) {    //a取完了
            num[i] = b[id2++];
            continue;
        }
        if (id2 == n2) {    //b取完了
            num[i] = a[id1++];
            continue;
        }
        if (a[id1] <= b[id2]) num[i] = a[id1++];
        else num[i] = b[id2++], res += n1 - id1;    //若a>b，加上逆序数
    }
}
void MergeSort(int l, int r) {

    if (l == r - 1) return;
    int m = (l + r) / 2;
    MergeSort(l, m);
    MergeSort(m, r);
    Merge(l, m, r);
}
int main() {

    ios::sync_with_stdio(false), cin.tie(), cout.tie();
    while (cin >> n >> x >> y) {
        for (int i = 0; i < n; i++) cin >> num[i];
        res = 0;
        MergeSort(0, n);
        cout << res * min(x, y) << endl;
    }

    return 0;
}

```