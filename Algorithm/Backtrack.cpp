#include <bits/stdc++.h>

using namespace std;

const int maxn = 105;

/******** triangle count ********/
int dfs(int a[], int n, int id) {
	
	if (id == n) {
		int _0 = 0, _1 = 0, half = n * (n + 1) / 4;
		for (int i = 0; i < n; i++) {	//calculate the 1st row
			a[i] ? (_1++) : (_0++);
			if (_0 > half or _1 > half) return 0;	//pruning
		}
		for (int i = n - 1; i >= 0; i--) {
			for (int j = 0; j < i; j++) {	//update the next row
				a[j] ^= a[j + 1];
				a[j] ? (_1++) : (_0++);
				if (_0 > half or _1 > half) return 0;
			}
		}
		return 1;
	}
	int res = 0;
	for (int i = 0; i < 2; i++) {	//try to mark 0 or 1
		a[id] = i;
		res += dfs(a, n, id + 1);
	}
	return res;
}
int triangleCount(int n) {	//calculate the amount of triangle(n rows, the i-th row has n-i elements) satisfying a[i][j] = a[i-1][j]^a[i-1][j+1]	
	
	if (n * (n + 1) % 4) return 0;	//return 0 when sum is odd number
	int a[maxn];
	return dfs(a, n, 0);
}
void triangleCountTest() {
	
	for (int i = 0; i < 5; i++) {
		printf("the amount of level %d triangle: %d\n", i, triangleCount(i));
	}
}
int main() {
	
	triangleCountTest();

	return 0;
}
