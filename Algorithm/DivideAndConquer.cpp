#include <bits/stdc++.h>

using namespace std;

/******** Chessboard Coverage ********/
const int maxn = 100;
int a[maxn][maxn], id;	//chessboard & mark number

void chess(int x0, int y0, int x, int y, int n) {	//(x0,y0)->base, (x,y)->, n->size 
	
	if (n == 1) return;
	int t = id++, s = n / 2;
	if (x < x0 + s and y < y0 + s) chess(x0, y0, x, y, s);	//left-up bad
	else {
		a[x0 + s - 1][y0 + s - 1] = t;	//mark right-down of the left-up sub-chessboard as new id
		chess(x0, y0, x0 + s - 1, y0 + s - 1, s);
	}
	
	if (x < x0 + s and y >= y0 + s) chess(x0, y0 + s, x, y, s);	//right-up bad
	else {
		a[x0 + s - 1][y0 + s] = t;
		chess(x0, y0 + s, x0 + s - 1, y0 + s, s);
	}
	
	if (x >= x0 + s and y < y0 + s) chess(x0 + s, y0, x, y, s);	//left-down bad
	else {
		a[x0 + s][y0 + s - 1] = t;
		chess(x0 + s, y0, x0 + s, y0 + s - 1, s);
	}
	
	if (x >= x0 + s and y >= y0 + s) chess(x0 + s, y0 + s, x, y, s);	//right-down bad
	else {
		a[x0 + s][y0 + s] = t;
		chess(x0 + s, y0 + s, x0 + s, y0 + s, s);
	}
}
void chessBoardTest() {	//test function
	
	int n = 8, x = 5, y = 5;	//n must be 2^k, (5, 5) is the bad block
	id = 0;
	a[x][y] = -1;
	chess(0, 0, x, y, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%-3d%c", a[i][j], j == n - 1 ? '\n' : ' ');
		}
	}
}

/******** find k-th smallest number ********/
int findK(int num[], int l, int r, int k) {	//range from l to r
	
	if (l == r) return num[l];
    int i = l, j = r, tmp;
    while (i < j) {		//once quick-sort
        tmp = a[i];
        while (i < j and a[j] >= tmp) j--;
        a[i] = a[j];
        while (i < j and a[i] <= tmp) i++;
        a[j] = a[i];
        a[i] = tmp;
    }
    tmp = i - l + 1;	//[l, i] <= [i + 1, r]
    if (k <= tmp) return findK(num, l, i, k);
    return findK(num, i + 1, r, k - tmp);
}
void findKTest() {	//test function
	
	int a[10] = {5, 0, 6, 9, 8, 4, 3, 7, 2, 1}; 
//	nth_element(a, a + 5, a + 10);
	findK(a, 0, 9, 5);
	for (int i = 0; i < 10; i++) {
		cout << a[i] << ' ';
	}	
}









