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
int selectPacId[maxn] = {}, pacLen = 0, maxValue = -inf;
void dfs3(int w[], int v[], int n, int left, bool a[], int id) {	//enumerate every condition & update (select[], maxValue)
	
	if (id == n) {
		int sum = 0;
		for (int i = 0; i < n; i++) {
			if (a[i]) sum += v[i];
		}
		if (sum > maxValue) {
			maxValue = sum;
			pacLen = 0;
			for (int i = 0; i < n; i++) {
				if (a[i]) selectPacId[pacLen++] = i;
			}
		}
		return;
	}
	if (left >= w[id]) {	//try to add id when it is possible
		a[id] = true;
		dfs3(w, v, n, left - w[id], a, id + 1);
	}
	a[id] = false;
	dfs3(w, v, n, left, a, id + 1);	//dismiss id
}
void package(int w[], int v[], int n, int all) {
	
	bool a[maxn] = {};
	dfs3(w, v, n, all, a, 0);
	cout << "max value of the 0-1 package: " << maxValue << "\nselected id of the packages: ";
	for (int i = 0; i < pacLen; i++) {
		cout << selectPacId[i] << " \n"[i == pacLen - 1];
	}
}
void packageTest() {	//test function
	
	int w[] = {2, 1, 3, 2}, v[] = {3, 2, 4, 2};
	int n = 4, all = 5;
	package(w, v, n, all);
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
int bestSum1 = -inf;	//maximum sum1 satisfying sum1 <= c1
bool selectLoad[maxn] = {};	//mark 1st ship whether select the package
void dfs5(int n, int sum, int w[], bool a[], int id) {
	
	if (id == n) {
		int ct = 0;
		for (int i = 0; i < n; i++) {
			if (a[i]) ct += w[i];
		}	
		if (ct > bestSum1) {	//if 1st ship could load more, then update result
			for (int i = 0; i < n; i++) {
				selectLoad[i] = a[i];
			}
			bestSum1 = ct;
		}
		return;
	}
	if (sum >= w[id]) {	//try to load id to 1st ship
		a[id] = true;
		dfs5(n, sum - w[id], w, a, id + 1);
	}
	a[id] = false;		//dismiss id
	dfs5(n, sum, w, a, id + 1);
}
void loading2(int c1, int c2, int n, int w[]) {	//load n package to 2 ships(maximum weights of them are c1 & c2)
	
	bool a[maxn] = {};	//temporary array
	dfs5(n, c1, w, a, 0);
	
	int sum1 = 0, sum2 = 0;
	for (int i = 0; i < n; i++) {
		selectLoad[i] ? (sum1 += w[i]) : (sum2 += w[i]);
	}
	printf("load-weight of the 2 ships: %d, %d\nship number of each package: ", sum1, sum2);
	for (int i = 0; i < n; i++) {
		printf("%d%c", selectLoad[i] ? 1 : 2, " \n"[i == n - 1]);
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
