#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using int64 = long long;

const int mods[29] = {
  1000000007, 1000000006, 500000002, 243900800, 79872000,
  19660800, 5242880, 2097152, 1048576, 524288,
  262144, 131072, 65536, 32768, 16384,
  8192, 4096, 2048, 1024, 512,
  256, 128, 64, 32, 16,
  8, 4, 2, 1
};

const int N = 1e6 + 10, S = 262144 * 3;

int p2[29][S];
char s[N];

int64 pow_mod(int64 a, int64 n, int64 mod) {
  if ((mod & (mod - 1)) == 0 && n > 30) return 0;
  int64 r = 1 % mod;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  for (int i = 0; i < 28; ++i) {
    p2[i][0] = 1;
    for (int j = 1; j < S; ++j) {
      p2[i][j] = p2[i][j - 1] * 2;
      if (p2[i][j] >= mods[i]) p2[i][j] -= mods[i];
    }
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    std::vector<int> ret(29);
    scanf("%s", s);
    int n = strlen(s), now = 0;
    for (int i = 0; i < n; ++i) {
      if (s[i] == '0') {
        now = std::min(now + 1, mods[0]);
        for (int j = 0; j < 28; ++j) {
          ++ret[j];
          if (ret[j] >= mods[j]) ret[j] -= mods[j];
        }
      } else if (s[i] == '1') {
        now = std::min(now * 2 + 2, mods[0]);
        for (int j = 0; j < 28; ++j) {
          ret[j] = ret[j] * 2 + 2;
          ret[j] %= mods[j];
        }
      } else if (s[i] == '2') {
        // x -> 3 * (2 ^ (x + 1) - 1)
        for (int j = 0, e; j < 28; ++j) {
          if (now + 1 < mods[j + 1]) e = now + 1;
          else e = ret[j + 1] + 1 + mods[j + 1];
          if (e < S) ret[j] = 3ll * (p2[j][e] - 1) % mods[j];
          else ret[j] = 3 * (pow_mod(2, e, mods[j]) - 1) % mods[j];
          if (ret[j] < 0) ret[j] += mods[j];
        }
        if (now <= 30) {
          now = std::min<long long>(mods[0], (3ll << (now + 1)) - 3);
        } else {
          now = mods[0];
        }
      }
    }
    printf("%d\n", ret[0]);
  }
  return 0;
}
