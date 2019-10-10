#include <bits/stdc++.h>
#include "../../Fundamental/Random.h"

using namespace std;

const int maxn =  105;
const int inf = INT_MAX / 2;
const int ctLimit = 10000000;	//shuffle-times limits
const int a[] = {1, 100, 10000, 1000000};	//number of executions
RandomNumber Rand;	//used to generate random numbers

/******** n-Queen ********/
bool QueenOK;	//mark whether problem is solved
bool idOK(int a[], int id) {	//check whether [0, id] is legal
 	
	for (int i = 0; i < id; i++) {
		if (a[i] == a[id] || abs(id - i) == abs(a[id] - a[i])) return false;
	}
	return true;
}
void nQueen(int a[], int n, int id) {	//trackback algorithm
	
	if (id == n) {
		for (int i = 0; i < n; i++) {	//output each queen's location
			printf("(%d, %d)%c", i, a[i], ",\n"[i == n - 1]);
		}
		QueenOK = true;
		return;
	}
	for (int i = 0; i < n and !QueenOK; i++) {	//try to set a[id] = i
		a[id] = i;
		if (idOK(a, id)) nQueen(a, n, id + 1);
	}
}
void nQueenRandom(int n) {	//n-Queen problem solved by LasVegas algorithm

	if (n == 1) {
		cout << "(0, 0)" << endl;
		return ;
	}
	QueenOK = false;
	int a[maxn];	//a[i] = j means exist a queen located at (i, j)
	for (int i = 0; i < n; i++) {
		a[i] = i;
	}
	for (int ct = 0; ct < ctLimit && !idOK(a, n / 2 - 1); ct++) {	//LasVegas part
		shuffle(a, n);
	}
	if (idOK(a, n / 2 - 1)) nQueen(a, n, n / 2);	//if the initial n/2 has legaled, try the other by trackback algorithm
	if (!QueenOK) cout << "(no result)" << endl;
}
void nQueenTest() {	//test function
	
	for (int i = 6; i <= 10; i++) {
		printf("one result of %d*%d Queen: ", i, i);
		nQueenRandom(i);
	}
}


/******** factorization ********/
int split(int n) {	//return 1 factor of n (if n <= 1, then return 1)
	
	for (int i = sqrt(n); i >= 2; i--) {
		if (n % i == 0) return i;
	}
	return 1;
}
int Pollard(int n) {	//return 1 factor of n (Pollard algorithm)
	
	int pre = Rand.Random(n - 1) + 1, now = pre, res;
	for (int i = 2, k = 2; i < ctLimit; i++) {
		now = (now * now - 1) % n;	//a[i] = (a[i - 1] ^ 2 - 1) mod n
		res = __gcd(pre - now, n);
		if (res > 1 and res < n) {	//success to find a factor
			return res;
		}
		if (pre == now) return now;
		if (i == k) {	//pre's id must be 2^t
			pre = now;
			k += k;
		}
	}
	return 1;	//when operate more than ctLimit times, return 1
}
void factorizationTest() {	//test function
	
	int a[] = {45, 286, 1024, 1025, 4509}, n = 5;
	for (int i = 0; i < n; i++) {
		printf("factor of %d: %d (split), %d (Pollard)\n", a[i], split(a[i]), Pollard(a[i]));
	}
}


/******** main ********/ 
int main() {
	
	nQueenTest();
	factorizationTest();
	
	return 0;
} 
