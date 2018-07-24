#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
#define int LL

const int mod = int(1e9 + 7);
const int maxn = 3005;

int dp1[maxn][maxn], dp2[maxn][maxn];
char a[maxn][maxn];
int n, m;

inline void work(int t[][maxn]) {

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] != '#') (t[i][j] += t[i - 1][j] + t[i][j - 1]) %= mod;
        }
    }
}
int32_t main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    if (a[1][1] == '#' or a[n][m] == '#' or a[1][2] == '#' or a[2][1] == '#'
        or a[n - 1][m] == '#' or a[n][m - 1] == '#') {
        cout << "0" << endl;
        return 0;
    }

    dp1[1][2] = dp2[2][1] = 1;
    work(dp1); work(dp2);

    cout << (dp1[n - 1][m] * dp2[n][m - 1] % mod - dp1[n][m - 1] * dp2[n - 1][m] % mod + mod) % mod << endl;

    return 0;
}