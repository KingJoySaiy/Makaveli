#include <bits/stdc++.h>

using namespace std;

const int maxn = int(1e5 + 5);

set<int> all;
int pre[maxn], res[maxn];
int n, m, ct, l, r;

void solve() {

    all.clear();
    cin >> n >> m;
    for (int i = 0; i < n; i++) all.insert(i + 1), pre[i] = i;
    while (m--) {
        cin >> l >> r;
        pre[r - 1] = min(pre[r - 1], l - 1);
    }
    for (int i = n - 1; i; i--) pre[i - 1] = min(pre[i - 1], pre[i]);

    for (int i = 0, t = 0; i < n; i++) {
        while (t < pre[i]) all.insert(res[t++]);
        res[i] = *all.begin();
        all.erase(res[i]);
    }
    for (int i = 0; i < n - 1; i++) cout << res[i] << ' ';
    cout << res[n - 1] << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> ct;
    while (ct--) solve();

    return 0;
}
