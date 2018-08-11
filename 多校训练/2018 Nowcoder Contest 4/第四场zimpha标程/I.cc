#include <cstdio>
#include <vector>
#include <cassert>
#include <functional>

const int N = 3e5 + 10, inf = 1e9;

struct node {
  int value;
  node* next;
} pool[N * 4];

int sz;

node* new_node(int v) {
  pool[sz].value = v;
  pool[sz].next = nullptr;
  return pool + (sz++);
}

int dp[N][3][3], prev[N][3][3];

std::vector<int> solve(std::vector<int> &a, std::vector<int> &b, std::vector<int> &c, int n, int& cost) {
  std::vector<int> cnt(n * 3);
  std::vector<bool> start(n * 3);
  std::vector<int> pred(n * 3, -1);
  for (int i = 0; i < n; ++i) {
    int x = std::min(b[i], c[i]);
    start[a[i]] = 1;
    pred[b[i]] = a[i];
    pred[c[i]] = a[i];
    if (x < a[i]) ++cnt[x], --cnt[a[i]];
  }
  for (int i = 1; i < n * 3; ++i) cnt[i] += cnt[i - 1];
  for (int i = 0; i < n * 3; ++i) {
    for (int x = 0; x < 3; ++x) {
      for (int y = 0; y < 3; ++y) {
        dp[i][x][y] = inf;
        prev[i][x][y] = -1;
      }
    }
  }
  auto update = [&](int &x, int &y, int s, int t) {
    if (s >= inf) return;
    if (s < x) x = s, y = t;
  };
  dp[0][1][0] = 2;
  if (cnt[0] == 0) dp[0][0][1] = 1;
  for (int i = 1; i < n * 3 - 1; ++i) {
    for (int j = 0; j < 3; ++j) {
      update(dp[i][2][j], prev[i][2][j], dp[i - 1][0][j] + 3, j);
      update(dp[i][1][j], prev[i][1][j], dp[i - 1][1][j] + 2, 4 + j);
      update(dp[i][2][j], prev[i][2][j], dp[i - 1][2][j] + 3, 8 + j);
      if (cnt[i] == 0) {
        if (j <= 1) update(dp[i][0][j], prev[i][0][j], dp[i - 1][0][j] + 1, j);
        if (j == 0) update(dp[i][0][j + 1], prev[i][0][j + 1], dp[i - 1][1][j] + 1, 4 + j);
        update(dp[i][0][j], prev[i][0][j], dp[i - 1][2][j] + 1, 8 + j);
      }
      if (j == 1) update(dp[i][1][j + 1], prev[i][1][j + 1], dp[i - 1][0][j] + 2, j);
    }
  }
  cost = inf;
  int x, y;
  if (dp[n * 3 - 2][1][2] < cost) {
    cost = dp[n * 3 - 2][1][2];
    x = 1, y = 2;
  }
  if (dp[n * 3 - 2][0][1] < cost) {
    cost = dp[n * 3 - 2][0][1];
    x = 0, y = 1;
  }
  if (cost == inf) return {};
  assert(cost != inf);
  // s1 is the start point
  node *s1 = nullptr, *t1 = nullptr, *s2 = nullptr, *t2 = nullptr;

  auto make_chain_2 = [&](int x, int y) -> std::pair<node*, node*> {
    node* s = new_node(x);
    node* t = new_node(y);
    s->next = t;;
    return {s, t};
  };

  auto make_chain_3 = [&](int x, int y) -> std::pair<node*, node*> {
    node* u = new_node(x);
    node* v = new_node(y);
    node* w = new_node(x);
    u->next = v;
    v->next = w;
    return {u, w};
  };

  auto front = [&](node* s, int x) -> node* {
    node* t = new_node(x);
    t->next = s;
    return t;
  };

  auto tail = [&](node* t, int x) -> node* {
    node* p = new_node(x);
    t->next = p;
    return p;
  };

  sz = 0;
  if (x == 0) {
    std::tie(s1, t1) = make_chain_2(3 * n - 2, 3 * n - 1);
  } else if (y != 0) {
    std::tie(s1, t1) = make_chain_3(3 * n - 2, 3 * n - 1);
  } else {
    std::tie(s1, t1) = make_chain_2(3 * n - 1, 3 * n - 2);
    s2 = t2 = new_node(3 * n - 2);
  }
  for (int i = n * 3 - 2; i >= 1; --i) {
    int tx = prev[i][x][y] >> 2;
    int ty = prev[i][x][y] % 4;
    if (x == 0) {
      if (tx == 0) {
        s1 = front(s1, i - 1);
      } else if (tx == 1) {
        s2 = s1, t2 = t1;
        s2 = front(s2, i - 1);
        std::tie(s1, t1) = make_chain_2(i, i - 1);
      } else {
        s2 = s1, t2 = t1;
        s2 = front(s2, i - 1);
        std::tie(s1, t1) = make_chain_3(i - 1, i);
      }
    } else if (x == 1) {
      if (tx == 0) {
        assert(s2 == nullptr);
        s1 = front(s1, i - 1);
      } else if (tx == 1) {
        if (s2 == nullptr) s1 = front(s1, i - 1), t1 = tail(t1, i - 1);
        else t1 = tail(t1, i - 1), s2 = front(s2, i - 1);
      } else {
        assert(false);
      }
    } else {
      if (tx == 0) {
        s1 = front(s1, i - 1);
        t1->next = s2->next;
        s2 = t2 = nullptr;
      } else if (tx == 1) {
        assert(false);
      } else {
        s1 = front(s1, i - 1);
        t1 = tail(t1, i - 1);
        s2 = front(s2, i - 1);
      }
    }
    x = tx, y = ty;
  }
  if (x == 1) t1->next = s2->next;
  assert(start[s1->value]);
  std::vector<int> ret;
  std::vector<bool> mark(n * 3);
  int length = 0;
  for (node* p = s1; p != nullptr; p = p->next) {
    ++length;
    if (mark[p->value]) continue;
    if (pred[p->value] == -1) {
      ret.push_back(p->value);
      mark[p->value] = 1;
    } else if (mark[pred[p->value]]) {
      ret.push_back(p->value);
      mark[p->value] = 1;
    }
  }
  assert(length - 1 == cost);
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d%d", &a[i], &b[i], &c[i]);
      --a[i], --b[i], --c[i];
    }
    int cost_s, cost_t;
    auto s = solve(a, b, c, n, cost_s);
    for (int i = 0; i < n; ++i) {
      a[i] = n * 3 - 1 - a[i];
      b[i] = n * 3 - 1 - b[i];
      c[i] = n * 3 - 1 - c[i];
    }
    auto t = solve(a, b, c, n, cost_t);
    if (cost_t < cost_s) {
      cost_s = cost_t;
      for (auto &&x: t) x = n * 3 - 1 - x;
      s = t;
    }
    assert(cost_s != inf);
    for (auto &&x: s) printf("%d ", x + 1);
    puts("");
  }
  return 0;
}
