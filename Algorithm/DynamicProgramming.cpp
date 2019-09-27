#include <bits/stdc++.h>

using namespace std;

const int maxn = 105;

/******** Matrix Chain ********/
void matrixChain(int a[], int n, int dp[][maxn],int s[][maxn]) {
	
	memset(dp, 0, sizeof(dp));	//initialization dp[i][i] = 0
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
	
	int a[] = {30, 35, 15, 5, 10, 20, 25}, n = 6;
	int dp[maxn][maxn], s[maxn][maxn];
	matrixChain(a, n, dp, s);
	showMatrix(s, 1, n);
}


/******** Longest Common sequence & subsrting ********/
int LCSeq(string a, string b, int n, int m, int dp[][maxn]) {	//subsequence
	
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
			else dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
		}
	}
	return dp[n][m];
}
int LCStr(string a, string b, int n, int m, int dp[][maxn]) {	//substring
	
	memset(dp, 0, sizeof(dp));
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
	int dp[maxn][maxn], n = a.length(), m = b.length();
	cout << "longest common sqeuence: " << LCSeq(a, b, n, m, dp) << endl;
	cout << "longest common substring: " << LCStr(a, b, n, m, dp) << endl;
}

/******** find maximun sum********/
int maxSum1(int *a, int n) {
	
	int res = 0, now = a[0];
	for (int i = 1; i < n; i++) {
		now = max(now + a[i], a[i]);
		res = max(res, now);	//if all of a[i] < 0, then res = 0
	}
	return res;
}
int maxSuum2(int a[][maxn], int n, int m) {
	
	//(need to update)
}
void maxSumTest() {	//test function
	
	int a[] = {4, -3, 5, -2, -1, 2, 6, -2}, n = 8;
	cout << maxSum1(a, n) << endl;
	
	
}
int main() {

	matrixChainTest();
	LCSTest(); 
	maxSumTest();
	
    return 0;
}





