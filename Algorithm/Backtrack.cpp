#include <bits/stdc++.h>

using namespace std;

const int maxn = 105;
const int inf = INT_MAX / 2;

/******** triangle count ********/
int dfs1(bool a[], int n, int id) {
	
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
		res += dfs1(a, n, id + 1);
	}
	return res;
}
int triangleCount(int n) {	//calculate the amount of triangle(n rows, the i-th row has n-i elements) satisfying a[i][j] = a[i-1][j]^a[i-1][j+1]	
	
	if (n * (n + 1) % 4) return 0;	//return 0 when sum is odd number
	bool a[maxn] = {};
	return dfs1(a, n, 0);
}
void triangleCountTest() {	//test function
	
	for (int i = 1; i <= 5; i++) {
		printf("level %d triangle: %d\n", i, triangleCount(i));
	}
}


/******** n-Queen ********/
int dfs2(int a[], int n, int id) {
	
	if (id == n) return 1;
	int res = 0;
	for (int i = 0; i < n; i++) {	//try to set a[id] = i
		bool ok = true;
		for (int j = 0; j < id; j++) {	//avoid the same row
			if (a[j] == i || abs(id - j) == abs(i - a[j])) {	//check whether on the same column/diagonal
				ok = false;
				break;
			}
		}
		if (ok) {	//if the rule satisfied, then search next row & update result
			a[id] = i;
			res += dfs2(a, n, id + 1);
		}
	}
	return res;
}
int nQueen(int n) {
	
	int a[maxn];	//a[i] = j means exist a queen located at (i, j)
	return dfs2(a, n, 0);
}
void nQueenTest() {	//test function
	
	for (int i = 6; i <= 10; i++) {
		printf("%d*%d Queen: %d\n", i, i, nQueen(i));
	}
}


/******** 0-1 package ********/
int dfs3(int w[], int v[], int n, int left, bool a[], int id) {
	
	if (id == n) {
		int res = 0;
		for (int i = 0; i < n; i++) {
			if (a[i]) res += v[i];
		}
		return res;
	}
	int res = -inf;
	if (left >= w[id]) {	//try to add id when it is possible
		a[id] = true;
		res = max(res, dfs3(w, v, n, left - w[id], a, id + 1));
	}
	a[id] = false;	//dismiss id
	return max(res, dfs3(w, v, n, left, a, id + 1));
}
int package(int w[], int v[], int n, int all) {
	
	bool a[maxn] = {};
	return dfs3(w, v, n, all, a, 0);
}
void packageTest() {	//test function
	
	int w[] = {2, 1, 3, 2}, v[] = {3, 2, 4, 2};
	int n = 4, all = 5;
	cout << "max value of the 0-1 package: " << package(w, v, n, all) << endl;
}


/******** n coloring problem ********/
int dfs4(bool a[][maxn], int n, int m, int res[], int id) {
	
	if (id == n) {
//		for (int i = 0; i < n; i++) {	//output each case
//			cout << res[i] << ' ';
//		}
//		cout << endl;
		return 1;	//count + 1
	}
	int ct = 0;
	for (int i = 1; i <= m; i++) {
		res[id] = i;	//color id-node as i
		bool ok = true;
		for (int j = 0; j < id; j++) {
			if (a[j][id] and res[j] == res[id]) {	//avoid 2 adjacent nodes have the same color
				ok = false;
				break;
			}
		}
		if (ok) ct += dfs4(a, n, m, res, id + 1);
		res[id] = 0;
	}
	return ct;
}
int nColoring(bool a[][maxn], int n, int m) {	//color n nodes by m different colors
	
	int res[maxn] = {};
	return dfs4(a, n, m, res, 0);
}
void nColoringTest() {	//test function
	
	int n = 5, m = 4, id = 0, data[] = {0, 2, 0, 4, 1, 2, 1, 3, 1, 4, 2, 3, 2, 4, 3, 4};
	bool a[maxn][maxn] = {};	//adjacency matrix
	for (int i = 0; i < 16; i += 2) {
		a[data[i]][data[i + 1]] = a[data[i + 1]][data[i]] = true;
	}
	printf("number of coloring %d node(s) by %d color(s): %d\n", n, m, nColoring(a, n, m));
}


/******** loading problem 2 ********/
bool loadOK;	//mark whether loading is finished
void dfs5(int n, int sum, int sum2, int w[], bool select[], int id) {
	
	if (!loadOK and id == n) {
		int ct = 0;
		for (int i = 0; i < n; i++) {
			if (!select[i]) ct += w[i];
		}	
		if (ct <= sum2) loadOK = true;	//if sum2 could load other packages then finished
		return;
	}
	if (!loadOK and sum >= w[id]) {	//try to load id to 1st ship
		select[id] = true;
		dfs5(n, sum - w[id], sum2, w, select, id + 1);
	}
	if (!loadOK) {	//dismiss id(load id to 2nd ship)
		select[id] = false;
		dfs5(n, sum, sum2, w, select, id + 1);
	}
}
void loading2(int c1, int c2, int n, int w[]) {	//load n package to 2 ships(maximum weight of them is c1 & c2)
	
	loadOK = false;
	bool select[maxn] = {};
	dfs5(n, c1, c2, w, select, 0);
	int sum1 = 0, sum2 = 0;
	for (int i = 0; i < n; i++) {
		select[i] ? (sum1 += w[i]) : (sum2 += w[i]);
	}
	printf("load-weight of the 2 ships: %d, %d\nship number of each package: ", sum1, sum2);
	for (int i = 0; i < n; i++) {
		printf("%d%c", select[i] ? 1 : 2, i == n - 1 ? '\n' : ' ');
	}
} 
void loading2Test() {	//test function
	
	int c1 = 55, c2 = 35, n = 4, w[] = {20, 15, 30, 20};
	loading2(c1, c2, n, w);
}


/******** main ********/
int main() {
	
	triangleCountTest();
	nQueenTest();
	packageTest();
	nColoringTest();
	loading2Test();
	
	return 0;
}
