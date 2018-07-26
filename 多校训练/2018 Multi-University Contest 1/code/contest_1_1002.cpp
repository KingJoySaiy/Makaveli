#include <bits/stdc++.h>

using namespace std;

const int maxn = int(1e5 + 5);
char s[maxn];
int n, ct;

struct data {

    int l, r, ct;
    bool operator<(const data &t) const {

        if (l > r and t.l <= t.r) return true;      //'('多的优先
        if (l <= r and t.l > t.r) return false;
        if (l > r and t.l > t.r) return r < t.r;    //都有多余的'('，则')'少的优先
        return l > t.l;                             //')'都比较多，则'('多的优先
    }
} a[maxn];

void solve() {

    cin >> n;
    memset(a, 0, sizeof(a));
    for (int i = 0; i < n; i++) {
        cin >> s;
        for (int j = 0, len = strlen(s); j < len; j++) {
            if (s[j] == '(') a[i].l++;
            else {
                if (a[i].l) a[i].l--, a[i].ct++;
                else a[i].r++;
            }
        }
    }
    sort(a, a + n);
    int left = 0, res = 0;
    for (int i = 0; i < n; i++) {
        a[i].r = min(a[i].r, left); //')'与多出来的'('匹配
        res += a[i].r + a[i].ct;
        left += a[i].l - a[i].r;    //加上多出来的'('
    }
    cout << 2 * res << endl;
}
int main() {

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> ct;
    while (ct--) solve();

    return 0;
}