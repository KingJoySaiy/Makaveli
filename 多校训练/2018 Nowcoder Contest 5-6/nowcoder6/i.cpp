#include <bits/stdc++.h>

#define ls(x) ((x) << 1)
#define rs(x) (ls(x) | 1)
#define mid ((l + r) >> 1)
#define lch ls(x), l, mid
#define rch rs(x), mid + 1, r

const int max_N = (1 << 18) + 21;
const int mod = 998244353;

int T, N, M, ans[max_N], a[max_N], tot;

std::pair<int, int> seg[max_N];

struct cmp {
        bool operator ()(const int &x, const int &y) {
                return seg[x].second < seg[y].second;
        }
};

std::vector<int> vec[max_N << 1];

#define ALL(x) vec[x].begin(), vec[x].end()

int ROUND_UP(int n) {
    int res = 1;
    while (res < n) res <<= 1;
    return res;
}

int qi, ql, qr, last;

int query(int x, int l, int r) {
    if (r <= ql) {
        int res = 0;
        while (!vec[x].empty() && seg[vec[x].back()].second >= qr) {
            if (!ans[vec[x].back()]) {
                ++res;
                ans[vec[x].back()] = qi;
                last = int(1ll * last * vec[x].back() % mod);
            }
            vec[x].pop_back();
        }
        return res;
    }
    int res = query(lch);
    if (ql > mid) res += query(rch);
    return res;
}

void testCase() {
    static int caseID = 0;
    scanf("%d%d", &N, &M);

    for (int i = 1; i <= N; ++i) {
        scanf("%d%d", &seg[i].first, &seg[i].second);
        a[i] = seg[i].first;
        ans[i] = 0;
    }
    std::sort(a + 1, a + 1 + N);
    tot = int(std::unique(a + 1, a + 1 + N) - (a + 1));
    int n = ROUND_UP(tot);
    for (int i = 1; i <= N; ++i) {
        int rk = int(std::lower_bound(a + 1, a + 1 + tot, seg[i].first) - a);
        vec[n + rk - 1].push_back(i);
    }
    for (int i = 0; i < N; ++i) {
        std::sort(ALL(i + n), cmp());
    }
    for (int i = n - 1; i; --i) {
        vec[i].resize(vec[ls(i)].size() + vec[rs(i)].size());
        std::merge(ALL(ls(i)), ALL(rs(i)), vec[i].begin(), cmp());
    }

    last = 0;

    printf("Case #%d: \n", ++caseID);
    for (qi = 1; qi <= M; ++qi) {
        scanf("%d", &qr);
        qr ^= last;
        last = 1;
        ql = int(std::upper_bound(a + 1, a + 1 + tot, qr) - a - 1);
        int res = ql? query(1, 1, n): 0;
        printf("%d\n", res);
        if (!res) last = 0;
    }
    for (int i = 1; i <= N; ++i) {
        printf("%d%c", ans[i], " \n"[i == N]);
    }
    for (int i = 1; i < (n << 1); ++i) {
        std::vector<int>().swap(vec[i]);
    }
}

int main() {
    scanf("%d", &T);
    while (T--) testCase();
    return 0;
}
