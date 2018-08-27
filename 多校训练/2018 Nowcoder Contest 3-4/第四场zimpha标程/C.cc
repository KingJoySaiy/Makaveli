#include <cstdio>
#include <algorithm>

using int64 = long long;

const int mod = 1e9 + 7;

int64 dp[80][140][2];
int64 prefix[80];

void prepare() {
  dp[1][70][1] = 1;
  for (int len = 1; len < 60; ++len) {
    for (int sum = 0; sum < 140; ++sum) {
      for (int last = 0; last < 2; ++last) {
        if (!dp[len][sum][last]) continue;
        dp[len + 1][sum + 1][last] += dp[len][sum][last];
        dp[len + 1][sum - 1][!last] += dp[len][sum][last];
      }
    }
  }
  for (int len = 1; len <= 60; ++len) {
    for (int sum = 0; sum < 140; ++sum) {
      for (int last = 0; last < 2; ++last) {
        prefix[len] += dp[len][sum][last] % mod * std::abs(sum - 70);
        prefix[len] %= mod;
      }
    }
  }
}

int main() {
  prepare();
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 n;
    scanf("%lld", &n);
    int64 ret = 0;
    int len = 0;
    while ((1ull << len) <= n) ++len;
    for (int i = 0; i < len; ++i) ret += prefix[i];
    int now = 0, last = -1;
    for (int i = len - 1; i >= 0; --i) {
      int o = n >> i & 1;
      if (o && i != len - 1) {
        int tmp = now;
        if (last != -1) {
          if (last == 0) ++tmp;
          else --tmp;
        }
        for (int sum = -i; sum <= i; ++sum) {
          int64 cnt = dp[i + 1][sum + 70][0] + dp[i + 1][sum + 70][1];
          ret += cnt % mod * std::abs(tmp + sum);
        }
      }
      if (last != -1) {
        if (last == o) ++now;
        else --now;
      }
      last = o;
    }
    ret += std::abs(now);
    printf("%lld\n", ret % mod);
  }
  return 0;
}
