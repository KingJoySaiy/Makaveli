#include <bits/stdc++.h>

using namespace std;

const int maxn = int(1e5 + 5);

int a[maxn], n, ct;

void solve() {

    long long res = 0, ct = 0;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    bool flag = true;
    int mi, t = 0;
    while (true) {
        if (flag) {
            while (t < n - 1 and a[t] >= a[t + 1]) t++;
            mi = a[t];
        } else {
            while (t < n - 1 and a[t] <= a[t + 1]) t++;
            res += a[t] - mi;
            ct++;
        }
        flag = !flag;
        if (t == n - 1) break;
    }
    cout << res << ' ' << 2 * ct << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> ct;
    while (ct--) solve();

    return 0;
}