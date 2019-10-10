#include <bits/stdc++.h>
#include "../../Fundamental/Random.h"

using namespace std;

const int maxn =  105;
const int inf = INT_MAX / 2;
const int ctLimit = 100;	//random or shuffle -times
RandomNumber Rand;	//used to generate random numbers

typedef pair<int, int> pp;
typedef long long LL;

/******** find major element *********/
int majority1(int a[], int n) {	//find major element of the array
	
	int ct = 1000;	//loop ctLimit times 
	while (ct--) {
		int sum = 0, res = a[Rand.Random(n)];
		for (int i = 0; i < n; i++) {
			sum += (a[i] == res);
		}
		if (sum >= (n + 1) / 2) return res;	//return if find the result
	} 
	return -1;	//fail to find the majority
}
bool majority2(pp a[], int n, int m) {	//check whether exist m points are collinear 
	
	if (m > n) return false;	//special condition 
	if(m == 1 or m == 2) return true;
	int ct = 1000;	//loop ctLimit times 
	while (ct--) {
		int sum = 0, x = Rand.Random(n), y = Rand.Random(n);
		if (x == y) continue;
		for (int i = 0; i < n; i++) {
			sum += ((a[x].second - a[i].second) * (a[y].first - a[i].first) == (a[y].second - a[i].second) * (a[x].first - a[i].first));
		}
		if (sum >= m) return true;
	}
	return false;
}
void majorityTest() {	//test function
	
	const int data[] = {-1, -1, 20, 1, 1, 20, 5, 5, 9, 9};
	int a[] = {1, 7, 10, 7, 1, 8, 7, 9, 8, 10, 10, 4, 10, 10, 10, 10, 8, 10, 10, 10}, nn = 20;
	pp b[maxn];
	int n = 5, m = 3, id = 0;
	for (int i = 0; i < n; i++) {
		b[i] = make_pair(data[id++], data[id++]);
	}
	printf("The majority of the array: %d\n", majority1(a, nn));	
	printf("Exist %d points are collinear: %s\n", m, majority2(b, n, m) ? "true" : "false");
}


/******** Miller-Rabin prime test ********/
LL mod_pow(LL x, LL n, LL mod) {   //return x^n % mod

    LL res = 1;
    while (n) {
        if (n % 2) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}
bool MillerRabin(LL n) {	//check whether n is a prime
	
	if (n == 2) return true;
    if (n < 2 || n % 2 == 0) return false;
    LL x = n - 1, t = 0;   
    while ((x & 1) == 0) {	//n - 1 = x * 2^t
        x >>= 1;
        t++;
    }
    int ct = ctLimit;	//loop ctLimit times 
    while (ct--) {
    	LL a = rand() % (n - 1) + 1;	//a^(x*2^t)%n == 1
		LL now = mod_pow(a, x, n), pre = now;
	    for (int i = 0; i < t; i++) {
	        now = now * now % n;
	        if (now == 1 && pre > 1 && pre < n - 1) return false;   //¶þ´ÎÌ½²â
	        pre = now;
	    }
	    if (now != 1) return false;	//Fermat's little theorem
	}
    return true;
}
void MillerRabinTest() {	//test function
	
	int n = 100, ct = 10, x;
	while (ct--) {
		x = Rand.Random(n);
		printf("%d is a prime: %s\n", x, MillerRabin(x) ? "true" : "false");
	}
}


/******** main ********/
int main() {
	
	majorityTest();	
	MillerRabinTest(); 
	
	return 0;
}

