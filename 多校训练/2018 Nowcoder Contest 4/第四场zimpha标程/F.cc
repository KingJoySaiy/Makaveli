#include <cstdio>
#include <algorithm>

using namespace std;
const int MAXN = 2000 + 10;
char a[MAXN][MAXN];
int N, M;

bool check(int x, int y) {
  return a[x][y] == a[x][M - y - 1] && a[x][y] == a[N - x - 1][y] &&
    a[x][y] == a[N - x - 1][M - y - 1];
}

int main() {
  int T; scanf("%d", &T);
  while (T --) {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; ++ i) {
      scanf("%s", a[i]);
    }
    int x = N / 2 - 1, y = M / 2 - 1;
    for (int i = 0; i < N / 2; ++ i) {
      for (int j = 0; j < M / 2; ++ j) {
        if (!check(i, j)) {
          x = std::min(x, i), y = std::min(y, j);
        }
      }
    }
    printf("%d\n", x * y);
  }
  return 0;
}
