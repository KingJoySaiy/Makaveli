#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using pii = std::pair<int, int>;

const int N = 2e5 + 10;
int a[N], n, sz, rt;
std::vector<int> edges[N << 1];
int deg[N << 1], val[N << 1];
int ls[N << 1], rs[N << 1], pt[N];

void build(int &o, int l, int r) {
  o = sz ++; val[o] = -1;
  if (l + 1 == r) {
    pt[l] = o;
    val[o] = a[l];
    return;
  }
  int m = (l + r) >> 1;
  build(ls[o], l, m);
  build(rs[o], m, r);
  edges[ls[o]].push_back(o);
  edges[rs[o]].push_back(o);
  deg[o] += 2;
}

void ins(int o, int l, int r, int L, int R, int x) {
  if (L <= l && R >= r) {
    edges[o].push_back(x);
    ++deg[x];
    return;
  }
  int m = (l + r) >> 1;
  if (L < m) ins(ls[o], l, m, L, R, x);
  if (R > m) ins(rs[o], m, r, L, R, x);
}

int main() {
  int T; scanf("%d", &T);
  for (int cas = 1; cas <= T; ++ cas) {
    scanf("%d", &n);
    sz = 0;
    std::vector<int> sum(n + 1);
    for (int i = 0; i < n; ++ i) {
      scanf("%d", a + i);
      sum[i] = (a[i]!= -1);
    }
    for (int i = n - 1; i >= 0; --i) {
      sum[i] += sum[i + 1];
    }
    bool valid = true;
    for (int i = 0; i < n; ++i) if (a[i] != -1 && a[i] % n != i) {
      int x = a[i] % n;
      if (x < i) {
        valid &= (sum[x] - sum[i] == i - x);
      } else {
        valid &= (sum[0] - sum[i] == i && sum[x] == n - x);
      }
    }
    if (!valid) {
      puts("-1");
      continue;
    }
    for (int i = 0; i < n * 2; ++ i) {
      edges[i].clear();
      deg[i] = 0;
    }
    build(rt, 0, n);
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> queue;
    for (int i = 0; i < n; ++ i) if (a[i] != -1) {
      if (a[i] % n != i) {
        int x = a[i] % n;
        if (x > i) {
          ins(rt, 0, n, 0, i, pt[i]);
          ins(rt, 0, n, x, n, pt[i]);
        } else {
          ins(rt, 0, n, x, i, pt[i]);
        }
      } else {
        queue.emplace(a[i], pt[i]);
      }
    }
    std::vector<int> ret;
    while (!queue.empty()) {
      int u = queue.top().second;
      int s = queue.top().first;
      if (s != -1) ret.push_back(s);
      queue.pop();
      for (auto &v: edges[u]) {
        if (--deg[v] == 0) {
          queue.emplace(val[v], v);
        }
      }
    }
    if (ret.size() != sum[0]) {
      puts("-1");
      continue;
    }
    for (size_t i = 0; i < ret.size(); ++ i) {
      if (i) putchar(' ');
      printf("%d", ret[i]);
    }
    puts("");
  }
  return 0;
}
