#include <bits/stdc++.h>

using namespace std;

const int maxn = 105;

/******** partial package ********/
struct package {
	
	double w, v;
	bool operator <(const package &t) const {
		return v / w > t.v / t.w;
	}
};
double partialPackage(package p[], int n, int all, double select[]) {
	
	double res = 0;
	sort(p, p + n);
	for (int i = 0; i < n; i++) {
		 if (all >= p[i].w) {
		 	select[i] = 1;
		 	all -= p[i].w;
		 	res += p[i].v;
		 } else {
		 	select[i] = all / p[i].w;
		 	res += select[i] * p[i].v;
		 	break;
		 }
	}
	return res;
}
void partialPackageTest() {
	
	double w[] = {10, 9, 11, 12, 7, 3}, v[] = {12, 9, 7, 9, 8, 4}, select[maxn];
	int n = 6, all = 30;
	package p[maxn];
	for (int i = 0; i < n; i++) {
		p[i].w = w[i];
		p[i].v = v[i];
	}
	printf("max value of the partial package: %.2f\n", partialPackage(p, n, all, select));
	for (int i = 0; i < n; i++) {
		printf("%.2f%c", select[i], i == n - 1 ? '\n' : ' ');
	}
}


/******** main ********/ 
int main() {

	partialPackageTest();
	

    return 0;
}

