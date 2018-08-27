#include <cstdio>

const int N = 1000 + 10;

int a[N][N];

void construct(int n) {
  for (int i = 0; i < n; i += 2) {
    int m = i + 2;
    a[m - 1][m - 1] = -1;
    a[m - 1][m - 2] = 1;
    a[m - 2][m - 2] = 1;
    a[m - 2][m - 1] = 0;
    for (int j = 0; j < i; ++j) {
      if (j & 1) a[j][m - 1] = a[j][m - 2] = a[m - 1][j] = a[m - 2][j] = -1;
      else a[j][m - 1] = a[j][m - 2] = a[m - 1][j] = a[m - 2][j] = 1;
    }
  }
}

int main() {
  int T;
  scanf("%d", &T);
  construct(200);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    if (n % 2 == 1) puts("impossible");
    else puts("possible");
    if (n % 2 == 0) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if (j) putchar(' ');
          printf("%d", a[i][j]);
        }
        puts("");
      }
    }
  }
  return 0;
}
