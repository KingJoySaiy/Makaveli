#include <bits/stdc++.h>
using namespace std;
const int N = 100005;

int n;
vector<pair<int,int>> e[N];

int s[N];
long long f[N] , h[N];

void dfs(int x , int fa) {
    s[x] = 1;
    f[x] = 0;
    for (auto &it : e[x]) {
        int y = it.first;
        if (y != fa) {
            dfs(y , x);
            s[x] += s[y];
            f[x] += f[y] + 1LL * s[y] * it.second;
        }
    }
}

void DFS(int x , int fa) {
    for (auto &it : e[x]) {
        int y = it.first;
        if (y != fa) {
            h[y] = h[x] + f[x] - f[y] + 1LL * (n - s[y] * 2) * it.second;
            DFS(y , x);
        }
    }
    f[x] += h[x];
}

long long work() {
    scanf("%d" , &n);
    for (int i = 1 ; i <= n ; ++ i) {
        e[i].clear();
    }
    for (int i = 1 ; i < n ; ++ i) {
        int x , y , w;
        scanf("%d%d%d" , &x , &y , &w);
        e[x].emplace_back(y , w);
        e[y].emplace_back(x , w);
    }
    dfs(1 , 0);
    DFS(1 , 0);
    sort(f + 1 , f + n + 1);
    long long res0 = 0 , res1 = 0;
    long long Q = 1e15;
    for (int i = 1 ; i <= n ; ++ i) {
        long long w = f[i] * (n - i);
        res0 += w % Q;
        res1 += w / Q;
        if (res0 >= Q) {
            res0 -= Q;
            res1 ++;
        }
    }
    if (res1) {
        printf("%lld%015lld\n" , res1 , res0);
    } else {
        printf("%lld\n" , res0);
    }
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --) {
        static int ca = 0;
        printf("Case #%d: ", ++ ca);
        work();
    }
}
