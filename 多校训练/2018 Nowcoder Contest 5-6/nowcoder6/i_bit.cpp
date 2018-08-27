#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n , m , X[N] , Y[N];
int d[N] , D , o[N] , v[N];
vector<int> c[N];

void work() {
    scanf("%d%d" , &n , &m);
    D = 0;
    for (int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d" , X + i , Y + i);
        d[D ++] = X[i];
    }
    sort(d , d + D);
    D = unique(d , d + D) - d;
    for (int i = 1 ; i <= n ; ++ i) {
        o[i] = i;
        X[i] = lower_bound(d , d + D , X[i]) - d + 1;
        c[i].clear();
        v[i] = 0;
    }
    sort(o + 1 , o + n + 1 , [&](int x , int y) {
            return Y[x] < Y[y];
        });
    for (int i = 1 ; i <= n ; ++ i) {
        int j = o[i];
        for (int k = X[j] ; k <= n ; k += k & -k) {
            c[k].emplace_back(j);
        }
    }
    int res = 0;
    for (int i = 1 ; i <= m ; ++ i) {
        int x;
        scanf("%d" , &x);
        x ^= res;
        int j = upper_bound(d , d + D , x) - d;
        int cnt = 0;
        res = 1;

        for (int k = j ; k > 0 ; k -= k & -k) {
            while (!c[k].empty() && Y[c[k].back()] >= x) {
                int w = c[k].back();
                if (!v[w]) {
                    v[w] = i;
                    ++ cnt;
                    res = (long long)res * w % 998244353;
                }
                c[k].pop_back();
            }
        }
        printf("%d\n" , cnt);
        if (cnt == 0) res = 0;
    }
    for (int i = 1 ; i <= n ; ++ i) {
        printf("%d%c" , v[i] , " \n"[i == n]);
    }
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --) {
        static int ca = 0;
        printf("Case #%d:\n" , ++ ca);
        work();
    }
}
