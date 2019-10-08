#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;
typedef long long LL;

const int S = 8;
LL a[100];   //记录n的所有因数
int nn, ct;

LL mod_mult(LL x, LL y, LL mod) {  //return x*y%mod

    LL res = 0;
    while (y) {
        if (y & 1) res = (res + x) % mod;
        x = (x << 1) % mod;
        y >>= 1;
    }
    return res;
}
LL mod_pow(LL x, LL n, LL mod) {   //return x^n%mod

    LL res = 1;
    while (n) {
        if (n & 1) res = mod_mult(res, x, mod);
        x = mod_mult(x, x, mod);
        n >>= 1;
    }
    return res;
}
bool check(LL a, LL n, LL x, LL t) {    //概率测试n是否为合数

    //a^(x2^t)%n == 1
    LL now = mod_pow(a, x, n), pre = now;
    for (int i = 0; i < t; i++) {
        now = mod_mult(now, now, n);
        if (now == 1 && pre != 1 && pre != n - 1) return true;   //二次探测
        pre = now;
    }
    return now != 1;
}
bool Miller_Rabin(LL n) {    //判断n是否为素数

    if (n == 2) return true;
    if (n < 2 || (n & 1) == 0) return false;
    LL x = n - 1, t = 0;   //n-1 = x*2^t
    while ((x & 1) == 0) {
        x >>= 1;
        t++;
    }
    for (int i = 0; i < S; i++) {
        LL a = rand() % (n - 1) + 1;
        if (check(a, n, x, t)) return false;
    }
    return true;
}
LL gcd(LL a, LL b) {  //求最小公因数

    LL res = b ? gcd(b, a % b) : a;
    return res < 0 ? -res : res;  //注意处理负数情况
}
LL pollard_rho(LL x, LL c) {  //求出x的一个因子

    LL i = 1, k = 2;
    LL x1 = rand() % (x - 1) + 1, x2 = x1;

    //(x1-x2)%p==0,n%(x1-x2)!=0
    while (1) {
        i++;
        x2 = (mod_mult(x2, x2, x) + c) % x;
        LL d = gcd(x1 - x2, x);
        if (d != 1 && d != x) return d;    //若gcd不为1则返回因子
        if (x1 == x2) return x;
        if (i == k) {
            x1 = x2;
            k += k;
        }
    }
}
void findfac(LL n, int k) {    //找出并记录因子

    if (n == 1) return;
    if (Miller_Rabin(n)) {
        a[nn++] = n;
        return;
    }
    LL p = n;
    while (p >= n) p = pollard_rho(p, k--);//值变化，防止k死循环
    findfac(p, k);   //深搜寻找因子
    findfac(n / p, k);
}
int main() {

    LL n;
    scanf("%d", &ct);
    while (ct--) {
        scanf("%I64d", &n);
        if (Miller_Rabin(n)) puts("Prime");
        else {
            nn = 0;
            findfac(n, 107);//c一般设为107左右即可
            LL res = a[0];
            for (int i = 1; i < nn; i++) res = min(res, a[i]);
            printf("%I64d\n", res);
        }
    }

    return 0;
}
