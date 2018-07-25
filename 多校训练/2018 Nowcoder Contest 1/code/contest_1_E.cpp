#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int mod = int(1e9 + 7);
const int maxn = int(1e5 + 5);

int a[maxn], pre[maxn], las[maxn];
LL dp[maxn][15];
int n, m, k;

void solve() {

    memset(pre, 0, sizeof(pre));
    memset(las, 0, sizeof(las));
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = las[a[i]];
        las[a[i]] = i;
        dp[i][0] = 1;
    }

    for (int i = dp[0][0] = 1; i <= n; i++) {
        for (int j = 0; j <= min(i, m); j++) {
            (dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]) %= mod;
            if (pre[i] and pre[i] + j >= i) {
                (dp[i][j] -= dp[pre[i] - 1][pre[i] + j - i] - mod) %= mod;
            }
        }
    }
    cout << dp[n][m] << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n >> m >> k) solve();

    return 0;
}
