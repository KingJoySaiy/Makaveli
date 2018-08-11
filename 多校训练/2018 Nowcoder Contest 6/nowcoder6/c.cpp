#include<bits/stdc++.h>

typedef long long ll;
const int moder = 998244353;
const int N = 1000010;

int inv[N];

void init(){
    inv[1] = 1;
    for (int i = 2; i < N; ++ i){
        inv[i] = (moder - 1ll * (moder / i) * inv[moder % i] % moder) % moder;
    }
}

int solve(ll n, ll m){
    int ret = 0, fac = 1, comb1 = m % moder, comb2 = 1;
    for (int i = 1; i <= std::min(n, m); ++ i){
        fac = 1ll * fac * i % moder;
        ret = (ret + 1ll * fac * comb1 % moder * comb2) % moder;
        comb1 = 1ll * comb1 * ((m - i) % moder) % moder * inv[i + 1] % moder;
        comb2 = 1ll * comb2 * ((n - i) % moder) % moder * inv[i] % moder;
    }
    return ret;
}

int main(){
    init();
    int test;
    scanf("%d", &test);
    for (int i = 1; i <= test; ++ i){
        ll n, m;
        scanf("%lld%lld", &n, &m);
        printf("Case #%d: %d\n", i, solve(n, m));
    }
    return 0;
}
