#include <bits/stdc++.h>
using namespace std;
const int N = 55;
const int Q = 998244353;

int n , s[N];
vector<int> e[N];

long long f[N][N * N / 2][N][2];
long long h[2][N * N / 2][N][2];
long long cnt[N * N / 2][2];

int inverse(int x) {
    return x == 1 ? 1 : (long long)(Q - Q / x) * inverse(Q % x) % Q;
}

void dfs(int x , int fa) {
    s[x] = 1;
    for (auto &y : e[x]) {
        if (y != fa) {
            dfs(y , x);
            s[x] += s[y];
        }
    }

    memset(h[0] , 0 , sizeof(h[0]));
    // White
    h[0][1][1][0] = 1;
    // Black
    h[0][0][0][1] = 1;
    int cur = 0 , nxt = 1 , sx = 1;

    for (auto &y : e[x]) {
        if (y == fa) continue;
        int sy = s[y];
        memset(h[nxt] , 0 , sizeof(h[nxt]));
        for (int i = 0 ; i <= sx * (sx + 1) / 2 ; ++ i) {
            for (int j = 0 ; j <= sx ; ++ j) {
                for (int k = 0 ; k < 2 ; ++ k) {
                    if (!h[cur][i][j][k]) continue;
                    for (int a = 0 ; a <= sy * (sy + 1) / 2 ; ++ a) {
                        for (int b = 0 ; b <= sy ; ++ b) {
                            for (int c = 0 ; c < 2 ; ++ c) {
                                if (!f[y][a][b][c]) continue;
                                h[nxt][i + a + j * b][j ? j + b : 0][k ^ c] +=
                                    h[cur][i][j][k] * f[y][a][b][c];
                            }
                        }
                    }
                }
            }
        }
        sx += sy;
        swap(cur , nxt);
    }
    memcpy(f[x] , h[cur] , sizeof(f[x]));
}

void work() {
    scanf("%d" , &n);
    for (int i = 1 ; i <= n ; ++ i) {
        e[i].clear();
    }
    for (int i = 1 ; i < n ; ++ i) {
        int x , y;
        scanf("%d%d" , &x , &y);
        e[x].emplace_back(y);
        e[y].emplace_back(x);
    }

    dfs(1 , 0);
    memset(cnt , 0 , sizeof(cnt));
    for (int i = 0 ; i <= n * (n + 1) / 2 ; ++ i) {
        for (int j = 0 ; j <= n ; ++ j) {
            for (int k = 0 ; k < 2 ; ++ k) {
                cnt[i][k] += f[1][i][j][k];
            }
        }
    }

    int res = 0;
    for (int i = 0 ; i < n * (n + 1) / 2 ; ++ i) {
        int a = i + i , b = n * (n + 1) , c = (b + Q - a) % Q;
        int d = (cnt[i][1] - cnt[i][0] % Q + Q) % Q;
        res += (long long)d * b % Q * inverse(c) % Q;
        res %= Q;
    }
    printf("%d\n" , res);
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --) {
        static int ca = 0;
        printf("Case #%d: " , ++ ca);
        work();
    }
}
