#include <bits/stdc++.h>
#include "../../Fundamental/Random.h"

using namespace std;

const int maxn =  105;
const int inf = INT_MAX / 2;
const int a[] = {1, 100, 10000, 1000000};	//number of executions
RandomNumber Rand;	//used to generate random numbers

/******** calculate ¦Ð ********/
double pi(int n) {	//calculate pi by n operations
	
	double x, y;
	int ct = 0;
	 for(int t = n; t--;) {
		x = Rand.fRandom();
		y = Rand.fRandom();
		ct += (x * x + y * y <= 1);
	} 
	return 4.0 * ct / n;
}
void piTest() {	//test function
	
	for (int i = 0; i < 4; i++) {
		printf("The estimate of pi (%d operations): %.4f\n", a[i], pi(a[i]));
	}
}


/******** calculate definite integral ********/
double F(double x) {
	return sin(x) + cos(x);
}
double definiteIntegral(double l, double r, int n) {	//return definite integral of F(x) range [l, r] by n operations
	
	double sum = 0;
	for (int t = n; t--; ) {
		sum += F((r - l) * Rand.fRandom() + l);
	}
	return (r - l) * sum / n;
}
void definiteIntegralTest() {	//test function 
	
	double l = 0, r = acos(-1);	//[0, pi]
	for (int i = 0; i < 4; i++) {
		printf("definite integral of F(x) range [%.2f, %.2f] (%d operations): %.4f\n", l, r, a[i], definiteIntegral(l, r, a[i]));
	}
}


/******** main ********/ 
int main() {
	
	piTest();
	definiteIntegralTest();
	
	return 0;
} 
