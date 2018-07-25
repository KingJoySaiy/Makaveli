#include <bits/stdc++.h>

using namespace std;

const int mod = 1440;
int ct, a, b, res, sign;
char x[50];

void solve() {

    scanf("%d%d%s", &a, &b, x);
    sign = x[3] == '+' ? 1 : -1;
    res = (6 * sign * int(10 * atof(x + 4) + 0.1) + a * 60 + b - 480 + mod) % mod;
    printf("%02d:%02d\n", res / 60, res % 60);
}
int main() {

    cin >> ct;
    while (ct--) solve();

    return 0;
}
