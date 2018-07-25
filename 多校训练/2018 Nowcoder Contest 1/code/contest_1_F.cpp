#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

const int mod = int(1e9 + 7);
const int maxn = 1020;

LL b[maxn][maxn], c[maxn][maxn];
LL a[maxn], d[2][maxn];
LL n, k, res;

LL mod_pow(LL x, LL n) {

    LL res = 1;
    while (n) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}
LL cal(LL n, LL k) {

    if (n <= 0) return 0;
    if (n <= k + 1) return c[k][n];
    LL res = 0;
    d[0][0] = d[1][k + 1] = 1;      //d[0][i] -> (0 ~ i)前缀积, d[1][i] -> (k + 1 ~ i)后缀积
    for (LL i = 1; i <= k + 1; i++) d[0][i] = d[0][i - 1] * (n - i + 1) % mod;
    for (LL i = k; i >= 0; i--) d[1][i] = d[1][i + 1] * (n - i - 1) % mod;
    for (LL i = 0; i <= k + 1; i++) {
        (res += (d[0][i] * d[1][i] % mod) * (b[k][i] * c[k][i] % mod) % mod) %= mod;
    }
    return res;
}
void ini() {

    for (int i = 1; i <= 1005; i++) {
        c[i][0] = 0;
        for (int j = 1; j <= i + 1; j++)
            c[i][j] = (c[i][j - 1] + mod_pow(j, i)) % mod;  //c[i] -> j ^ (1 ~ i) 前缀和

        for (int j = 0; j <= i; j++) {
            if (i == 1) {
                b[i][0] = mod_pow(2, mod - 2);
                b[i][1] = mod_pow(-1, mod - 2);
            } else {
                b[i][j] = b[i - 1][j] * mod_pow(j - (i + 1), mod - 2) % mod;
            }
        }
        b[i][i + 1] = 1;
        for (int j = 0; j <= i; j++) b[i][i + 1] = b[i][i + 1] * (i + 1 - j) % mod;
        b[i][i + 1] = mod_pow(b[i][i + 1], mod - 2);     //b[i] -> mod下 (-1 ~ i + 1) 前缀积的逆元
    }
}
void solve() {

    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + 1 + n);
    a[0] = res = 0;
    LL vv = 1;
    for (int i = 1; i <= n; i++) {
        k = n - i + 1;      //从大到小分段计算
        LL vv2 = (mod_pow(a[i], k + 1) - mod_pow(a[i - 1], k + 1) - cal(a[i] - 1, k) + cal(a[i - 1] - 1, k)) % mod;
        (res += vv * vv2 % mod) %= mod;
        (vv *= a[i]) %= mod;
    }
    while (res < 0) res += mod;
    cout << res << endl;
}
int main() {
    
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    ini();
    while (cin >> n) solve();

    return 0;
}





