#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int, int> pp;
struct ppp {

    int x, y, id;
    bool operator < (const ppp &t) const {
        return x < t.x or x == t.x and y < t.y;
    }
};

const int maxn = 1005;
ppp a[3 * maxn];
int ct, n, m;

void solve() {

    cin >> n;
    m = 3 * n;
    for (int i = 0; i < m; i++) {
        cin >> a[i].x >> a[i].y;
        a[i].id = i + 1;
    }
    sort(a, a + m);
    for (int i = 0; i < m; i += 3)
        cout << a[i].id << ' ' << a[i + 1].id << ' ' << a[i + 2].id << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    cin >> ct;
    while (ct--) solve();


    return 0;
}