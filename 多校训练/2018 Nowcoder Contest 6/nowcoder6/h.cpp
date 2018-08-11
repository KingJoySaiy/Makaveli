#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
vector<int> fac[N];
int c , z , m;
int d[10] , e[10] , f[10];
long long res;
vector<pair<int ,int>> factor;

void init() {
    for (int i = 2 ; i < N ; ++ i) {
        if (fac[i].empty()) {
            for (int j = i ; j < N ; j += i) {
                fac[j].emplace_back(i);
            }
        }
    }
}

int power(int A , int p , int e) {
    for (int i = 0 ; i < e ; ++ i) {
        if (1LL * A * p > m) {
            A = m + 1;
            return A;
        } else {
            A *= p;
        }
    }
    return A;
}

void dfs(int k , int A , int B, const int &x , const int &y ) {
    assert(A <= m && B <= m);
    if (k == factor.size()) {
        if (A > 1 && B > 1) {
            ++ res;
        }
    } else {
        int p = factor[k].first , z = factor[k].second;
        // d0 * x + e0 * y = z
        long long a0 = A;
        for (int d0 = 0 ; d0 * x <= z && a0 <= m ; ++ d0 , a0 *= p) {
            if ((z - d0 * x) % y) continue;
            int e0 = (z - d0 * x) / y;
            int b0 = power(B , p, e0);
            if (b0 > m) {
                continue;
            }
            dfs(k + 1 , a0 , b0 , x , y);
        }
    }
}

void exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
    } else {
        exgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }
}

inline int divide(int a , int b) {
    if (a < 0) {
        int c = -a / b + 1;
        return (a + c * b) / b - c;
    } else {
        return a / b;
    }
}

int line(int a , int b , int c) {
    // ax + by = c, 1 <= x,y <= m
    int d = __gcd(a , b);
    if (c % d) return 0;
    a /= d, b /= d, c /= d;

    int X , Y;
    exgcd(a , b , X , Y);
    X *= c , Y *= c;
    assert(a * X + b * Y == c);

    // a (X + kb) + b (Y - ka) = c , k is any int
    int lower = max(divide(1 - X + b - 1, b) , divide(Y - m + a - 1 , a));
    int upper = min(divide(m - X , b) , divide(Y - 1 , a));
    return max(0 , upper - lower + 1);
}

long long work() {
    scanf("%d%d%d" , &c , &z , &m);

    if (c == 1 || z == 0) {
        //a => [1 , m] , b = 0  => m
        //a => 1 , b => [1 , m] => m
        return 4LL * m * m;
    }

    factor.clear();
    for (auto &p : fac[c]) {
        int x = c, y = 0;
        while (x % p == 0) {
            x /= p;
            y += z;
        }
        factor.emplace_back(p , y);
    }
    reverse(factor.begin() , factor.end());

    res = 0;

    // a^x == c^z
    for (int x = 1 ; x <= m ; ++ x) {
        int A = 1 , flag = 1;
        for (auto &it : factor) {
            if (it.second % x) {
                flag = 0;
                break;
            }
            A = power(A , it.first, it.second / x);
            if (A > m) break;
        }
        if (flag && A <= m) {
            res += 4 * m;
        }
    }

    // a, b > 1 && x, y > 0
    int pfirst = factor[0].first , zfirst = factor[0].second;
    for (int d0 = 0 , a0 = 1 ; d0 <= zfirst ; ++ d0, a0 *= pfirst) {
        long long b0 = 1;
        for (int e0 = 0 ; e0 <= zfirst && b0 <= m ; ++ e0, b0 *= pfirst) {
            if (!d0 && !e0) continue;
            bool liner = true;

            int A = a0, B = b0;
            assert(0 < A && A <= m);
            assert(0 < B && B <= m);

            for (int j = 1 ; j < factor.size() ; ++ j) {
                int psecond = factor[j].first;
                int zsecond = factor[j].second;
                for (int dj = 0 , aj = A ; dj <= zsecond ; ++ dj, aj *= psecond) {
                    long long bj = B;
                    for (int ej = 0 ; ej <= zsecond && bj <= m; ++ ej, bj *= psecond) {
                        int delta = d0 * ej - e0 * dj;
                        if (!delta) continue;
                        int dX = zfirst * ej - e0 * zsecond;
                        if (dX % delta) continue;
                        int x = dX / delta;
                        int dY = d0 * zsecond - zfirst * dj;
                        if (dY % delta) continue;
                        int y = dY / delta;
                        if (x < 1 || x > m || y < 1 || y > m) continue;
                        dfs(j + 1 , aj , bj , x , y);
                    }
                    if (1LL * aj * psecond > m) break;
                }

                if (d0 * zsecond % zfirst || e0 * zsecond % zfirst) {
                    liner = false;
                    break;
                }
                d[j] = d0 * zsecond / zfirst;
                e[j] = e0 * zsecond / zfirst;
                A = power(A , psecond, d[j]);
                B = power(B , psecond, e[j]);
                if (A > m || B > m) {
                    liner = false;
                    break;
                }
            }

            if (liner && A > 1 && B > 1) {
                // d0 * x + e0 * y = z
                // x, y [1 , m]
                assert(d0 && e0);
                res += line(d0 , e0 , zfirst);
            }
        }
        if (1LL * a0 * pfirst > m) break;
    }
    return res;
}

int main(int argc, char *argv[]) {
    init();
    int T;
    scanf("%d" , &T);
    while (T --) {
        static int ca = 0;
        printf("Case #%d: %lld\n" , ++ ca, work());
    }
}
