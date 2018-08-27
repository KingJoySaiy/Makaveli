#include <bits/stdc++.h>
using namespace std;

long long work() {
    int n , m , k;
    scanf("%d%d%d" , &n , &m , &k);
    vector<int> w(m);
    for (int i = 0 ; i < k ; ++ i) {
        int x , y , z;
        scanf("%d%d%d" , &x, &y , &z);
        w[y - 1] = max(w[y - 1] , z);
    }
    long long res = 0;
    for (int i = 0 ; i < m; ++ i) {
        res += w[i];
    }
    return res;
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --) {
        static int ca = 0;
        printf("Case #%d: %lld\n" , ++ ca , work());
    }
}
