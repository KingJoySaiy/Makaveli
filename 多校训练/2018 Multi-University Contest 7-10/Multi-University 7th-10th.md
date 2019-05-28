* [Multi-University contest 7](http://acm.hdu.edu.cn/userloginex.php?cid=808)
* [Multi-University contest 8](http://acm.hdu.edu.cn/userloginex.php?cid=809)
## 7_1001. Age of Moyu
```c++
#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pp;          //first -> to, second -> num

const int inf = (INT_MAX >> 1) - 10;
const int maxn = int(1e5 + 5);
vector<pp> a[maxn];
int res[maxn];
int x, y, num, n, m;

struct data {

    int id, pre_num, cost;
    data (int id = 0, int pre_num = 0, int cost = 0) : id(id), pre_num(pre_num), cost(cost) {}
    data& operator = (const data &t) {
        id = t.id, pre_num = t.pre_num, cost = t.cost;
        return *this;
    }
    bool operator < (const data &t) const {
        return cost > t.cost;
    }
};

void dijstra(int x) {

    priority_queue<data> que;
    fill(res, res + maxn, inf);
    res[x] = 0;
    que.push(data(x, -1, 0));
    data t;
    while (!que.empty()) {
        t = que.top(); que.pop();
        for (auto &p : a[t.id]) {
            if (res[p.first] > res[t.id] + (t.pre_num != p.second)) {
                res[p.first] = res[t.id] + (t.pre_num != p.second);
                que.push(data(p.first, p.second, res[p.first]));
            }
        }
    }
}
void solve() {

    for (int i = 0; i < maxn; i++) a[i].clear();
    while (m--) {
        cin >> x >> y >> num;
        a[x].emplace_back(y, num);
        a[y].emplace_back(x, num);
    }
    dijstra(1);
    cout << (res[n] == inf ? -1 : res[n]) << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(), cout.tie();
    while (cin >> n >> m) solve();

    return 0;
}
```