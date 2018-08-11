#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    m = n - m;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
    }
    std::sort(a.begin(), a.end());
    std::vector<std::pair<int, int>> cnt;
    for (int i = 0, j; i < n; i = j) {
      for (j = i; j < n && a[i] == a[j]; ++j);
      cnt.emplace_back(j - i, a[i]);
    }
    std::sort(cnt.begin(), cnt.end());
    std::reverse(cnt.begin(), cnt.end());
    int ret = -1, rest = n;
    for (int i = 0, j; i < (int)cnt.size(); i = j) {
      for (j = i; j < (int)cnt.size() && cnt[i].first == cnt[j].first; ++j) {
        rest -= cnt[j].first;
      }
      for (int k = i; k < j; ++k) {
        if (cnt[k].first >= m) {
          ret = std::max(ret, cnt[k].second);
        } else if (m - cnt[k].first <= (j - 1) * (cnt[k].first - 1) + rest) {
          ret = std::max(ret, cnt[k].second);
        }
      }
    }
    printf("%d\n", ret);
  }
  return 0;
}
