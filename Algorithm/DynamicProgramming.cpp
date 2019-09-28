#include <bits/stdc++.h>

using namespace std;

const int maxn = 105;

/******** Matrix Chain ********/
void matrixChain(int a[], int n, int s[][maxn]) {
	
	int dp[maxn][maxn] = {};	//initialization dp[i][i] = 0
	for (int len = 2; len <= n; len++) {
		for (int i = 1; i <= n - len + 1; i++) {
			int j = i + len - 1;
			dp[i][j] = dp[i + 1][j] + a[i - 1] * a[i] * a[j];	//k = i, [i : k][k+1 : j]
			s[i][j] = i;
			for (int k = i + 1; k < j; k++) {	//k range [i+1, j-1]
				int tmp = dp[i][k] + dp[k + 1][j] + a[i - 1] * a[k] * a[j];
				if(tmp < dp[i][j]) {
					dp[i][j] = tmp;
					s[i][j] = k;
				}
			}
		}
	}
}
void showMatrix(const int s[][maxn], int i, int j) {	//show Matrix, the order indicated by brackets 
	
	if (i == j) printf("A[%d]", i);
	else {
		putchar('(');
		showMatrix(s, i, s[i][j]);
		showMatrix(s, s[i][j] + 1, j);
		putchar(')');
	}
}
void matrixChainTest() {	//test function
	
	int a[] = {30, 35, 15, 5, 10, 20, 25}, s[maxn][maxn], n = 6;
	matrixChain(a, n, s);
	showMatrix(s, 1, n);
	cout << endl;
}


/******** Longest Common sequence & subsrting ********/
int LCSeq(string a, string b, int n, int m) {	//subsequence
	
	int dp[maxn][maxn] = {};
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
			else dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
		}
	}
	return dp[n][m];
}
int LCStr(string a, string b, int n, int m) {	//substring
	
	int dp[maxn][maxn] = {};
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
			else dp[i][j] = 0;
		}
	}
	int res = INT_MIN;	//find maximum dp[i][j]
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			res = max(res, dp[i][j]);
		}
	}
	return res;
}
void LCSTest() {	//test function
	
	string a = "123ABCD4567", b = "ABE12345D6";
	int n = a.length(), m = b.length();
	cout << "longest common sqeuence: " << LCSeq(a, b, n, m) << endl;
	cout << "longest common substring: " << LCStr(a, b, n, m) << endl;
}


/******** find maximun sum********/
int maxSum1(int *a, int n) {	//max sum sequence
	
	int res = 0, now = 0;
	for (int i = 0; i < n; i++) {
		now = max(now + a[i], a[i]);	//add a[i] or rebegin from a[i]
		res = max(res, now);	//if all of a[i] < 0, then res = 0
	}
	return res;
}
int maxSum2(int a[][maxn], int n, int m) {	//max sum matrix
	 
	for (int i = 1; i < n; i++) {	//calculate the sum of the each column's prefix
		for (int j = 0; j < m; j++) {
			a[i][j] += a[i - 1][j];
		}	
	}
	int res = 0, now = 0, tmp;
	for (int i = 0; i < n; i++) {	//from i-th row to j-th row
		for (int j = i; j < n; j++) {
			now = 0;
			for (int k = 0; k < m; k++) {	//the same as maxSumSqeuence
				tmp = a[j][k] - (i == 0 ? 0 : a[i - 1][k]);
				now = max(now + tmp, tmp);
				res = max(res, now);
			}
		}
	}
	return res;
}
void maxSumTest() {	//test function
	
	int a[] = {2, -3, 5, -2, -1, 2, 6, -2, 0, 9, -4, -5}, n = 12;
	cout << "max sum of the sequence: " <<maxSum1(a, n) << endl;
	
	int b[maxn][maxn], N = 3, M = 4;
	for (int i = 0, t = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			b[i][j] = a[t++];
		}
	} 
	cout << "max sum of the matrix: " << maxSum2(b, N, M) << endl;
}


/******** 0-1 package ********/
int package(int w[], int v[], int n, int all) {
	
	int dp[maxn][maxn] = {};
	for (int i = 0 ;i < n; i++) {
		for (int j = 0; j <= all; j++) {
			if (j < w[i]) dp[i + 1][j] = dp[i][j];	//insufficient capacity
			else dp[i + 1][j] = max(dp[i][j], dp[i][j - w[i]] + v[i]);
		}
	}
	return dp[n][all];
}
void packageTest() {	//test function
	
	int w[] = {2, 1, 3, 2}, v[] = {3, 2, 4, 2};
	int n = 4, all = 5;
	cout << "max value of the 0-1 package: " << package(w, v, n, all) << endl;
}


/******** main ********/ 
int main() {

	matrixChainTest();
	LCSTest(); 
	maxSumTest();
	packageTest();
	
    return 0;
}





