#include<bits/stdc++.h>

typedef long long ll;

struct BigInteger{ // 仅支持非负整数
    static const int N = 150;
    static const int base = 1e6; // 修改它时记得修改输入输出格式

    int a[N];
    int length;

    BigInteger():length(0){memset(a, 0, sizeof(a));}

    BigInteger(ll p){
        memset(a, 0, sizeof(a));
        length = 0;
        if (!p) return;
        for (ll x = std::abs(p); x; x /= base){
            a[length ++] = x % base;
        }
    }

    int &operator [](int sit){return a[sit];}

    bool operator < (const BigInteger &q)const{
        if (length != q.length) return length < q.length;
        for (int i = length - 1; ~i; -- i){
            if (a[i] != q.a[i]) return a[i] < q.a[i];
        }
        return false;
    }

    BigInteger operator + (const BigInteger &p)const{
        BigInteger ret;
        ret.length = std::max(length, p.length) + 1;
        for (int i = 0; i < ret.length; ++ i){
            ret.a[i] += a[i] + p.a[i];
            if (ret.a[i] >= base) ret.a[i] -= base, ++ ret.a[i + 1];
        }
        for ( ; ret.length && !ret.a[ret.length - 1]; -- ret.length)
            ;
        return ret;
    }

    BigInteger operator - (const BigInteger &p)const{
        BigInteger ret;
        ret.length = length;
        for (int i = 0; i < ret.length; ++ i){
            ret.a[i] += a[i] - p.a[i];
            if (ret.a[i] < 0) ret.a[i] += base, -- ret.a[i + 1];
        }
        for ( ; ret.length && !ret.a[ret.length - 1]; -- ret.length)
            ;
        return ret;
    }

    BigInteger operator * (const BigInteger &p)const{
        static ll aux[N << 1];
        memset(aux, 0, sizeof(ll) * (length + p.length));
        for (int i = 0; i < length; ++ i){
            for (int j = 0; j < p.length; ++ j){
                aux[i + j] += (ll) a[i] * p.a[j];
            }
        }
        BigInteger ret;
        ret.length = p.length + length;
        for (int i = 0; i < ret.length; ++ i){
            aux[i + 1] += aux[i] / base;
            aux[i] %= base;
        }
        for ( ; ret.length && !aux[ret.length - 1]; -- ret.length)
            ;
        for (int i = 0; i < ret.length; ++ i) ret.a[i] = aux[i];
        return ret;
    }

    void write(){
        if (!length) return (void) printf("0");
        printf("%d", a[length - 1]);
        for (int i = length - 2; ~i; -- i){
            printf("%06d", a[i]);
        }
    }
};

const int N = 2010;
const int M = 16;

char s[N][M + 10];
std::vector <int> e[N << 1];
BigInteger dp[N << 1][2], power[N];
int sz[N << 1];

void init(){
    power[0] = BigInteger(1);
    for (int i = 1; i < N; ++ i){
        power[i] = power[i - 1] + power[i - 1];
    }
}

void dfs(int u){
    sz[u] = e[u].size() == 0;
    for (auto v : e[u]){
        dfs(v);
        sz[u] += sz[v];
    }
    if (e[u].empty()){
        dp[u][0] = BigInteger(1);
        dp[u][1] = BigInteger(1);
        return;
    }
    std::sort(e[u].begin(), e[u].end());
    BigInteger b[4], c[2], d[2];
    for (int i = 0; i < 2; ++ i){
        if (i == 0){
            c[0] = dp[e[u][0]][0];
            c[1] = power[sz[e[u][0]]] - c[0];
        }
        else{
            c[1] = dp[e[u][0]][1];
            c[0] = power[sz[e[u][0]]] - c[1];
        }
        for (int j = 0; j < 2; ++ j){
            if (j == 0){
                d[0] = dp[e[u][1]][0];
                d[1] = power[sz[e[u][1]]] - d[0];
            }
            else{
                d[1] = dp[e[u][1]][1];
                d[0] = power[sz[e[u][1]]] - d[1];
            }
            for (int v = 0; v < 2; ++ v){
                for (int w = 0; w < 2; ++ w){
                    b[v << 1 | w] = c[v] * d[w];
                }
            }
            for (int k = 0; k < 16; ++ k){
                if (s[u][k] == '0'){
                    continue;
                }
                BigInteger e[2];
                for (int v = 0; v < 4; ++ v){
                    auto &w = e[k >> v & 1];
                    w = w + b[v];
                }
                for (int v = 0; v < 2; ++ v){
                    dp[u][v] = std::max(dp[u][v], e[v]);
                }
            }
        }
    }
}

void solve(){
    for (int i = 0; i < N << 1; ++ i){
        e[i].clear();
    }
    for (int i = 0; i < N << 1; ++ i){
        for (int j = 0; j < 2; ++ j){
            dp[i][j] = BigInteger(0);
        }
    }
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; ++ i){
        scanf("%s", s[i]);
    }
    for (int i = 2, fa; i <= 2 * n - 1; ++ i){
        scanf("%d", &fa);
        e[fa].push_back(i);
    }
    dfs(1);
}

int main(){
    init();
    int test;
    scanf("%d", &test);
    for (int i = 1; i <= test; ++ i){
        solve();
        printf("Case #%d: ", i);
        dp[1][1].write();
        putchar('\n');
    }
    return 0;
}
