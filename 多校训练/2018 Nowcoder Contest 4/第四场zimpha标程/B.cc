#include <cstdio>
#include <algorithm>
#include <vector>

const int inf = 1e9;

struct SegmentTree {
  std::vector<int> u;
  int n;
  void init(int n) { //[0, n)
    this->n = n;
    u.assign(n * 2, inf);
  }
  void set(int p, int v) {
    p += n;
    for (u[p] = std::min(v, u[p]); p > 1; p >>= 1) {
      u[p >> 1] = std::min(u[p], u[p ^ 1]);
    }
  }
  int ask(int l, int r) { // [l, r)
    int res = inf;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) res = std::min(res, u[l++]);
      if (r & 1) res = std::min(res, u[--r]);
    }
    return res;
  }
};

struct interval {
  int l, r, w;
  bool operator < (const interval& other) const {
    return r < other.r;
  }
};

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<interval> s(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d%d", &s[i].l, &s[i].r, &s[i].w);
    }
    std::sort(s.begin(), s.end());
    std::vector<SegmentTree> st(n);
    int ret = inf;
    for (int i = 0; i < n; ++i) {
//      printf("start %d %d: \n", s[i].l, s[i].r);
      st[i].init(m + 1);
      if (s[i].l == 1) {
        st[i].set(0, 0);
      } else {
        for (int j = 0; j < i; ++j) if (s[j].r + 1 >= s[i].l) {
          int now = st[j].ask(s[j].l - 1, s[i].l);
          if (now == inf) continue;
          if (s[j].r + 1 == s[i].l) now = std::max(now, s[j].w);
          else now = std::max(now, s[j].w + s[i].w);
//          printf("  update: %d %d %d\n", s[j].l, s[j].r, now);
          st[i].set(s[j].r, now);
        }
      }
      if (s[i].r == m) {
        int now = st[i].ask(s[i].l - 1, s[i].r);
        now = std::max(now, s[i].w);
        ret = std::min(ret, now);
      }
    }
    if (ret == inf) ret = -1;
    printf("%d\n", ret);
  }
  return 0;
}
