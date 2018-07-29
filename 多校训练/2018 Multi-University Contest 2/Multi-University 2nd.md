* [Multi-University contest 2](http://acm.hdu.edu.cn/userloginex.php?cid=803)
## 1004. Game
* **题目大意** ： 2人删除从`1~n`的数字，每次删一个数并删除其所有因子，2人都采取最优策略，问先手是赢是输。
* **大体思路** ： 这题先手要么必胜要么必输，因为1是任何数的因子，先删其他任何数都将把1删掉。假设后手必胜，那么先手只需先把1删掉即可变成先手必胜。其实打出20个表发现全是`Yes`也应该大胆猜一下先手稳赢。

```c++
#include <bits/stdc++.h>

int main() {
    
    for (int n; std::cin >> n; puts("Yes"));
    
    return 0;
}
```
## 1007. Naive Operations

## 1010. Swaps and Inversions