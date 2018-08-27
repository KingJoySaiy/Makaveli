#include <bits/stdc++.h>
using namespace std;
unsigned a[10000000];

unsigned x, y, z;
unsigned tang() {
    unsigned t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;
    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;
    return z;
}

void testCase() {
    static int Case = 0;
    int n;
    scanf("%d%u%u%u", &n, &x, &y, &z);
    for (int i = 0 ; i < n ; ++ i) {
        a[i] = tang();
    }
    int m = max(0 , n - 100);
    nth_element(a , a + m , a + n);
    unsigned long long ans = 0;
    for (int i = m ; i < n ; ++ i) {
        for (int j = i + 1 ; j < n ; ++ j) {
            ans = max(ans , 1ull * a[i] / __gcd(a[i] , a[j]) * a[j]);
        }
    }
    printf("Case #%d: %llu\n", ++ Case, ans);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t --) {
        testCase();
    }
    return 0;
}
