#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>
#include <cstring>

using int64 = long long;

const int N = 2e6 + 10;

char s[N], buf[N * 2];

template <class T, class Compare = std::less<T>>
class SchieberVishkinRMQ {
public:
  SchieberVishkinRMQ() = default;

  void build(const std::vector<T> &a) {
    build(a.data(), a.size());
  }

  void build(const T *a, int n) {
    std::vector<int> left(n, -1), right(n, -1);
    std::vector<int> stk(n);
    // build Cartesian Tree
    for (int i = 0, top = 0; i < n; ++i) {
      int last = -1;
      while (top && compare(a[i], a[stk[top - 1]])) {
        last = stk[--top];
      }
      if (top) right[stk[top - 1]] = i;
      left[i] = last;
      stk[top++] = i;
    }

    // find preorder
    int root = stk[0];
    std::vector<int> parents(n, -1), order;
    indices.resize(n), inlabel.resize(n);
    for (int top = 1; top; ) {
      int u = stk[--top];
      order.push_back(u);
      indices[u] = inlabel[u] = order.size();
      if (left[u] != -1) {
        stk[top++] = left[u];
        parents[left[u]] = u;
      }
      if (right[u] != -1) {
        stk[top++] = right[u];
        parents[right[u]] = u;
      }
    }

    // calc helper structures for Schieber-Vishkin LCA
    ascendant.resize(n), head.resize(n);
    for (int i = n - 1; i > 0; --i) {
      int v = order[i], p = parents[v];
      if (lowbit(inlabel[p]) < lowbit(inlabel[v])) {
        inlabel[p] = inlabel[v];
      }
    }
    ascendant[root] = 0;
    for (int i = 1; i < n; ++i) {
      int v = order[i], p = parents[v];
      ascendant[v] = ascendant[p] | lowbit(inlabel[v]);
    }
    head[0] = root;
    for (int i = 1; i < n; ++i) {
      int v = order[i], p = parents[v];
      if (inlabel[v] != inlabel[p]) head[indices[v] - 1] = p;
      else head[indices[v] - 1] = head[indices[p] - 1];
    }
  }

  // return the index of the minimum value in [u, v] in O(1)
  int query(int u, int v) const {
    uint Iv = inlabel[v], Iu = inlabel[u];
    uint hIv = lowbit(Iv), hIu = lowbit(Iu);
    uint mask = highbit((Iv ^ Iu) | hIv | hIu) - 1;
    uint j = lowbit(ascendant[v] & ascendant[u] & ~mask);
    int x, y;
    if (j == hIv) x = v;
    else {
      mask = highbit(ascendant[v] & (j - 1)) - 1;
      x = head[((indices[v] & ~mask) | (mask + 1)) - 1];
    }
    if (j == hIu) y = u;
    else {
      mask = highbit(ascendant[u] & (j - 1)) - 1;
      y = head[((indices[u] & ~mask) | (mask + 1)) - 1];
    }
    return indices[x] < indices[y] ? x : y;
  }

private:
  using uint = unsigned int;
  static uint lowbit(uint x) {
    return x & (~x + 1); // x & (-x) or x & (x ^ (x - 1))
  }
  static uint highbit(uint x) {
    return 1u << (31 - __builtin_clz(x));
  }

  Compare compare;
  std::vector<uint> indices;
  std::vector<uint> inlabel;
  std::vector<uint> ascendant;
  std::vector<int> head;
};

#define pushS(x) sa[--cur[(int)s[x]]] = x
#define pushL(x) sa[cur[(int)s[x]]++] = x
class SuffixArray {
public:
  std::vector<int> sa;
  std::vector<int> rank;
  std::vector<int> lcp;
  SchieberVishkinRMQ<int> lcpRMQ;

  template <class T> void build(const T *s, int n);
  template <class T> void build(const T *s, int n, int m);

  int size() const {
    return sa.size() - 1;
  }
  int computeLCP(int i, int j) const {
    if (i == j) return size() - i;
    int x = rank[i], y = rank[j];
    if (x > y) std::swap(x, y);
    return lcp[lcpRMQ.query(x + 1, y)];
  }

private:
  using SLTypes = std::vector<bool>;
  int *buffer, *freq, *cur;
  int len;

  void buildRankTable();
  void buildLCPArrayRMQ();
  template <class T> void computeLCPArray(const T *s);
  template <class T> void countFrequency(const T *s, int n, int m);
  template <class T> void induce(const T *s, int *sa, int m, const SLTypes &t);
  template <class T> void sa_is(const T *s, int *sa, int n, int m);
};

template <class T>
void SuffixArray::build(const T *s, int n) {
  this->len = n;
  int m = *std::max_element(s, s + n) + 1;
  build(s, n, m);
  buildRankTable();
  computeLCPArray(s);
  buildLCPArrayRMQ();
}

template <class T>
void SuffixArray::build(const T *s, int n, int m) {
  sa.resize(n + 1);
  if (n == 0) sa[0] = 0;
  else {
    // memory usage: sa + buffer + types
    // = 4 * (n + max(m * 2, n)) + 2 * n / 8 + O(1) bytes
    std::vector<int> buffer((std::max(m, (n + 1) / 2) + 1) * 2);
    this->buffer = &buffer[0];
    sa_is<T>(s, &sa[0], n + 1, m);
  }
}

void SuffixArray::buildRankTable() {
  int n = size() + 1;
  rank.resize(n);
  for (int i = 0; i < n; ++i) rank[sa[i]] = i;
}

void SuffixArray::buildLCPArrayRMQ() {
  lcpRMQ.build(&lcp[0], size() + 1);
}

template <class T>
void SuffixArray::computeLCPArray(const T *s) {
  const int n = size() + 1;
  lcp.resize(n);
  for (int i = 0, h = lcp[0] = 0; i < n; ++i) {
    if (!rank[i]) continue;
    int j = sa[rank[i] - 1];
    while (i + h < n && j + h < n && s[i + h] == s[j + h]) ++h;
    if ((lcp[rank[i]] = h)) --h;
  }
}

template <class T>
void SuffixArray::countFrequency(const T *s, int n, int m) {
  memset(freq, 0, sizeof(int) * m);
  for (int i = 0; i < n; ++i) ++freq[(int)s[i]];
  for (int i = 1; i < m; ++i) freq[i] += freq[i - 1];
  memcpy(cur, freq, sizeof(int) * m);
}

template <class T>
void SuffixArray::induce(const T *s, int *sa, int m, const SLTypes &t) {
  const int n = t.size();
  memcpy(cur + 1, freq, sizeof(int) * (m - 1));
  for (int i = 0; i < n; ++i) {
    int p = sa[i] - 1;
    if (p >= 0 && t[p]) pushL(p);
  }
  memcpy(cur, freq, sizeof(int) * m);
  for (int i = n - 1; i > 0; --i) {
    int p = sa[i] - 1;
    if (p >= 0 && !t[p]) pushS(p);
  }
}

template <class T>
void SuffixArray::sa_is(const T *s, int *sa, int n, int m) {
  SLTypes t(n); memset(sa, 0, sizeof(int) * n);
  for (int i = n - 2; ~i; --i) {
    t[i] = (s[i] == s[i + 1]) ? t[i + 1] : s[i] > s[i + 1];
  }
  freq = buffer, cur = buffer + m;
  countFrequency(s, n, m);
  for (int i = 1; i < n; ++i) if (t[i - 1] > t[i]) pushS(i);
  induce(s, sa, m, t);
  int n1 = 0, order = 0;
  for (int i = 0, p; i < n; ++i) {
    if ((p = sa[i]) && t[p - 1] > t[p]) sa[n1++] = p;
  }
  int *s1 = sa + n1;
  memset(s1, -1, sizeof(int) * (n - n1));
  s1[(sa[0] - 1) / 2] = order++;
  for (int i = 1; i < n1; ++i) {
    bool diff = true;
    for (int x = sa[i - 1], y = sa[i]; ; ++x, ++y) {
      if (s[x] != s[y] || t[x] != t[y]) break;
      else if (t[x] > t[x + 1] && t[y] > t[y + 1]) {
        diff = (s[x + 1] != s[y + 1]); break;
      }
    }
    s1[(sa[i] - 1) / 2] = (order += diff) - 1;
  }
  for (int i = 0, x = 0; i < n - n1; ++i) {
    if (~s1[i]) s1[x++] = s1[i];
  }
  if (order != n1) {
    sa_is<int>(s1, sa, n1, order);
    for (int i = 0; i < n1; ++i) s1[sa[i]] = i;
  }
  for (int i = 1, j = 0; i < n; ++i) {
    if (t[i - 1] > t[i]) sa[s1[j++]] = -i;
  }
  memset(s1, 0, sizeof(int) * (n - n1));
  freq = buffer, cur = buffer + m;
  countFrequency(s, n, m);
  for (int i = n1 - 1; ~i; --i) pushS(-sa[i]);
  induce(s, sa, m, t);
}

std::vector<int> manacher(char *s, int n) {
  std::vector<int> u(n <<= 1, 0);
  for (int i = 0, j = 0, k; i < n; i += k, j = std::max(j - k, 0)) {
    while (i >= j && i + j + 1 < n && s[(i - j) >> 1] == s[(i + j + 1) >> 1]) ++j;
    for (u[i] = j, k = 1; i >= k && u[i] >= k && u[i - k] != u[i] - k; ++k) {
      u[i + k] = std::min(u[i - k], u[i] - k);
    }
  }
  return u;
}

std::vector<int> ext_kmp(char *s, int n) {
  std::vector<int> z(n, 0);
  for (int i = 1, x = 0, y = 0; i < n; ++i) {
    if (i <= y) z[i] = std::min(y - i, z[i - x]);
    while (i + z[i] < n && s[i + z[i]] == s[z[i]]) ++z[i];
    if (y <= i + z[i]) x = i, y = i + z[i];
  }
  z[0] = n;
  return z;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    std::vector<int> cnt(26);
    scanf("%s", s);
    int n = strlen(s);
    for (int i = 0; i < n; ++i) ++cnt[s[i] - 'a'];

    // length of pal center at i
    std::vector<int> diameter = manacher(s, n);
    for (int i = 0; i < n; ++i) {
      buf[i] = s[i];
      buf[i + n] = s[n - 1 - i];
    }

    // lcp of s[..i] and rev(s[..i])
    std::vector<int> prefix = ext_kmp(buf, n * 2);
    for (int i = 0; i < n; ++i) prefix[i] = prefix[n + n - 1 - i];
    for (int i = 0; i < n; ++i) {
      buf[i + n] = s[i];
      buf[i] = s[n - 1 - i];
    }
    // lcp of s[i..] and rev(s[i..])
    std::vector<int> suffix = ext_kmp(buf, n * 2);
    for (int i = 0; i < n; ++i) suffix[i] = suffix[i + n];

    SuffixArray sa;
    for (int i = 0; i < n; ++i) {
      buf[i] = s[i];
      buf[i + n] = s[n - 1 - i];
    }
    buf[n * 2] = 0;
    sa.build(buf, n * 2);

    bool find = false;
    std::vector<int> head(n, -1), value(n * 4), next(n * 4);
    int size = 0;
    auto put = [&](int x, int y) {
      if (x > y) std::swap(x, y);
      if (s[x] != s[y]) {
        value[size] = y;
        next[size] = head[x];
        head[x] = size++;
      }
    };

    auto diff = [&](int l, int r) -> std::pair<int, int> {
      int len = r - l + 1, pal = diameter[l + r];
      if (l == 0 && prefix[r] * 2 + pal == len - 2) {
        return {prefix[r], r - prefix[r]};
      }
      if (r == n - 1 && suffix[l] * 2 + pal == len - 2) {
        return {l + suffix[l], r - suffix[l]};
      }
      return {-1, -1};
    };

    for (int i = 0; i + 1 < n; ++i) {
      // [..i] and [i+1..]
      bool left = diameter[i] == i + 1;
      bool right = diameter[i + n] == n - i - 1;
      int a, b, c, d;
      if (left && right) {
        if ((i + 1) % 2 == 1 && (n - i - 1) % 2 == 1) put(i / 2, (i + n) / 2);
        find = true;
      } else if (left && !right) {
        std::tie(c, d) = diff(i + 1, n - 1);
        if (c == -1) {
          int len = n - i - 1, pal = diameter[n + i];
          int front = suffix[i + 1], rest = (len - pal) / 2 - front - 2;
          a = i + 1 + front, d = n - 1 - front;
          b = i + 1 + front + 1 + rest, c = n - 1 - front - 1 - rest;
          if (sa.computeLCP(a + 1, n + n - d) == rest) {
            if (s[a] == s[c] && s[b] == s[d]) {
              put(c, d);
              put(a, b);
            }
            if (s[a] == s[b] && s[c] == s[d]) {
              put(b, d);
              put(a, c);
            }
          }
        } else {
          if ((i + 1) % 2 == 1 && s[i / 2] == s[c]) {
            put(i / 2, d);
          }
          if ((i + 1) % 2 == 1 && s[i / 2] == s[d]) {
            put(i / 2, c);
          }
          if ((n - i - 1) % 2 == 1 && s[(n + i) / 2] == s[c]) {
            put((n + i) / 2, d);
          }
          if ((n - i - 1) % 2 == 1 && s[(n + i) / 2] == s[d]) {
            put((n + i) / 2, c);
          }
        }
      } else if (!left && right) {
        std::tie(a, b) = diff(0, i);
        if (a == -1) {
          int len = i + 1, pal = diameter[i];
          int front = prefix[i], rest = (len - pal) / 2 - front - 2;
          a = front, d = i - front;
          b = front + 1 + rest, c = i - front - 1 - rest;
          if (sa.computeLCP(a + 1, n + n - d) == rest) {
            if (s[a] == s[c] && s[b] == s[d]) {
              put(c, d);
              put(a, b);
            }
            if (s[a] == s[b] && s[c] == s[d]) {
              put(b, d);
              put(a, c);
            }
          }
        } else {
          if ((i + 1) % 2 == 1 && s[i / 2] == s[a]) {
            put(i / 2, b);
          }
          if ((i + 1) % 2 == 1 && s[i / 2] == s[b]) {
            put(i / 2, a);
          }
          if ((n - i - 1) % 2 == 1 && s[(n + i) / 2] == s[a]) {
            put((n + i) / 2, b);
          }
          if ((n - i - 1) % 2 == 1 && s[(n + i) / 2] == s[b]) {
            put((n + i) / 2, a);
          }
        }
      } else {
        std::tie(a, b) = diff(0, i);
        std::tie(c, d) = diff(i + 1, n - 1);
        if (a == -1 || c == -1) continue;
        if (s[a] == s[c] && s[b] == s[d]) {
          put(b, c);
          put(a, d);
        }
        if (s[a] == s[d] && s[b] == s[c]) {
          put(b, d);
          put(a, c);
        }
      }
    }

    int64 ret = 0;
    std::vector<bool> mark(n);
    for (int i = 0; i < n; ++i) {
      for (int it = head[i]; ~it; it = next[it]) {
        if (!mark[value[it]]) ++ret;
        mark[value[it]] = 1;
      }
      for (int it = head[i]; ~it; it = next[it]) {
        mark[value[it]] = 0;
      }
    }
    if (find) {
      for (auto &&x : cnt) ret += (int64)x * (x - 1) / 2;
    }
    printf("%lld\n", ret);
    fflush(stdout);
  }
  return 0;
}
