#include <bits/stdc++.h>

using namespace std;

const int mod = int(1e9 + 7);
const int maxn = int(1e5 + 5);

long long res[maxn], dp[maxn];
int q, k, l, r;

int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> q >> k;
    for (int i = 0; i < k; i++) res[i] = 1;
    for (int i = k; i < maxn; i++) {
        res[i] = res[i - 1] + dp[i - 1] % mod;
        dp[i] = res[i - k];
    }
    res[0] = dp[0] = 0;
    for (int i = 1; i < maxn; i++) {
        (res[i] += res[i - 1] + dp[i]) %= mod;
    }

    while (q--) {
        cin >> l >> r;
        cout << (res[r] - res[l - 1] + mod) % mod << endl;
    }

    return 0;
}