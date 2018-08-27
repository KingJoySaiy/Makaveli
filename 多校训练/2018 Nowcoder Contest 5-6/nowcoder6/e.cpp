#include <bits/stdc++.h>
using namespace std;
const int N = 505;
const int M = 1005;

int w , n , m;
vector<int> trans[N];
int s[M] , f[M] , t[M];
int nxt[12][N][M];

int par[N][N] , solo[N];

void work() {
    scanf("%d%d%d" , &w , &n , &m);
    for (int i = 0 ; i < w ; ++ i) {
        scanf("%d" , &t[i]);
        -- t[i];
    }
    for (int i = 0 ; i < n ; ++ i) {
        int k , x;
        scanf("%d" , &k);
        trans[i].clear();
        for (int j = 0 ; j < k ; ++ j) {
            scanf("%d" , &x);
            trans[i].push_back(-- x);
        }
    }
    for (int i = 0 ; i < m ; ++ i) {
        scanf("%d" , &s[i]);
        -- s[i];
    }
    for (int i = 1 ; i < m ; ++ i) {
        int j = f[i];
        while (j && s[i] != s[j]) {
            j = f[j];
        }
        f[i + 1] = (s[i] == s[j]) ? j + 1 : 0;
    }
    for (int i = 0 ; i < n ; ++ i) {
        nxt[1][i][m] = m;
        for (int j = 0 ; j < m ; ++ j) {
            int k = j;
            while (k && s[k] != i) {
                k = f[k];
            }
            if (s[k] == i) ++ k;
            nxt[1][i][j] = k;
        }
    }
    for (int k = 2 ; k <= 11 ; ++ k) {
        for (int i = 0 ; i < n ; ++ i) {
            nxt[k][i][m] = m;
            for (int j = 0 ; j < m ; ++ j) {
                int x = j;
                for (auto &y : trans[i]) {
                    x = nxt[k - 1][y][x];
                }
                nxt[k][i][j] = x;
            }
        }
    }
    int res = 1 << 30;
    for (int k = 1 ; k <= 11 ; ++ k) {
        int x = 0;
        for (int i = 0 ; i < w ; ++ i) {
            x = nxt[k][t[i]][x];
        }
        if (x == m) {
            res = min(res , k);
        }
    }

    memset(par , -1 , sizeof(par));
    memset(solo , -1 , sizeof(solo));
    queue<int> Q;
    for (int i = 0 ; i < w ; ++ i) {
        int x = t[i];
        if (!~solo[x]) {
            Q.push(~x) , solo[x] = 1;
        }
        if (i + 1 < w) {
            int y = t[i + 1];
            if (!~par[x][y]) {
                Q.push(x);
                Q.push(y);
                par[x][y] = 1;
            }
        }
    }
    while (!Q.empty()) {
        int x = Q.front(); Q.pop();
        if (x < 0) {
            x = ~x; int z = -1;
            for (auto &y : trans[x]) {
                if (!~solo[y]) {
                    solo[y] = solo[x] + 1;
                    Q.push(~y);
                }
                if (~z) {
                    if (!~par[z][y]) {
                        par[z][y] = solo[x] + 1;
                        Q.push(z);
                        Q.push(y);
                    }
                }
                z = y;
            }
        } else {
            int y = Q.front(); Q.pop();
            int nx = trans[x].back();
            int ny = trans[y][0];
            if (!~par[nx][ny]) {
                par[nx][ny] = par[x][y] + 1;
                Q.push(nx);
                Q.push(ny);
            }
        }
    }
    for (int i = 0 ; i < n ; ++ i) {
        for (int j = 0 ; j < n ; ++ j) {
            if (!~par[i][j]) continue;
            for (int k = 1 ; k <= 11 ; ++ k) {
                int x = nxt[k][i][0];
                x = nxt[k][j][x];
                if (x == m) {
                    res = min(res , par[i][j] + k - 1);
                }
            }
        }
    }

    if (res == 1 << 30)
        puts("-1");
    else {
        printf("%d\n" , res - 1);
    }
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
