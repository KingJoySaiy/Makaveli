#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int maxn = 10;
bool a[maxn][maxn], b[maxn][maxn];
unordered_set<LL> all;
int f[maxn];
int n, m1, m2, x, y;

void solve() {

    memset(a, false, sizeof(a));
    memset(b, false, sizeof(b));
    for (int i = 0; i < n; i++) f[i] = i;
    all.clear();

    while (m1--) {
        cin >> x >> y; x--, y--;
        a[x][y] = a[y][x] = true;
    }
    while (m2--) {
        cin >> x >> y; x--, y--;
        b[x][y] = b[y][x] = true;
    }
    do {
        LL t = 0ll;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (!a[i][j]) continue;
                if (b[x = f[i]][y = f[j]]) {
                    if (x > y) swap(x, y);
                    t |= LL(1) << (x * n + y);
                } else goto ed;
            }
        }
        all.insert(t);
        ed: continue;
    } while (next_permutation(f, f + n));
    cout << all.size() << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n >> m1 >> m2) solve();

    return 0;
}