#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int maxn = int(1e5 + 5);
LL f[maxn], n, mod;

void solve() {

    f[0] = f[1] = 0ll % mod;
    f[2] = f[3] = 1ll % mod;
    for (LL i = 4ll; i <= n; i++) {
        f[i] = ((i - 1) * f[i - 1] % mod
                + (i - 1) * f[i - 2] % mod
                - (i - 1) * (i - 2) / 2 % mod * f[i - 3] % mod
                + mod) % mod;
    }
    cout << f[n] << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n >> mod) solve();

    return 0;
}
/*
f(x) = (n - 1) * [f(n - 1) + f(n - 2)] - (n - 1) * (n - 2) / 2 * f(n - 3)
value: 0, 0, 1, 1, 6, 22 ...
index: 0, 1, 2, 3, 4, 5  ...
 */
