#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

const int mod = int(1e9 + 7);

LL b[63] = {1}, n;
int ct;

LL work(LL x) {

    LL res = 0;
    while (x) {
        res += x;
        x >>= 1;
    }
    return res;
}
void solve() {

    cin >> n;
    if (!--n) {
        cout << 1 << endl;
        return;
    }
    LL l = 0, r = n + 1, m;
    while (r - l > 1) {
        if (work(m = (l + r) / 2) < n) l = m;  //找到 (fun ≤ n) 的最大值
        else r = m;                             //r -> f[n], l = r - 1
    }
    LL res = ((n - work(l)) % mod) * (r % mod) % mod;

    for (int i = 1; b[i - 1] < r; i++) {
        LL k = ((r - 1 - b[i - 1]) / b[i] + 1) % mod;
        LL sum = (b[i - 1] % mod * k % mod + k * (k - 1) / 2 % mod * (b[i] % mod) % mod) % mod;
        res = (res + i * sum % mod) % mod;
    }
    cout << (res + 1 + mod) % mod << endl;
}

int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    for (int i = 1; i < 63; i++) b[i] = 2 * b[i - 1];
    cin >> ct;
    while (ct--) solve();

    return 0;
}