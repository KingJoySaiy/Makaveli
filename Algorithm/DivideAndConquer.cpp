#include <bits/stdc++.h>

using namespace std;

/******** Chessboard Coverage ********/
const int maxn = 100;
int a[maxn][maxn], mark;	//chessboard & mark number

void chess(int x0, int y0, int x, int y, int n) {	//(x0,y0)->base, (x,y)->, n->size 
	
	if (n == 1) return;
	int t = mark++, s = n / 2;
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
	mark = 0;
	a[x][y] = -1;
	chess(0, 0, x, y, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%-3d%c", a[i][j], j == n - 1 ? '\n' : ' ');
		}
	}
}


/******** find k-th smallest number ********/
int findK(int a[], int l, int r, int k) {	//range from l to r
	
	if (l == r) return a[l];
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
    if (k <= tmp) return findK(a, l, i, k);
    return findK(a, i + 1, r, k - tmp);
}
void findKTest() {	//test function
	
	int a[10] = {5, 0, 6, 9, 8, 4, 3, 7, 2, 1}; 
//	nth_element(a, a + 5, a + 10);
	findK(a, 0, 9, 5);
	for (int i = 0; i < 10; i++) {
		cout << a[i] << ' ';
	}
	cout << endl;
}


/******** find distance of closest pair ********/
struct point {
	double x, y;
	bool operator<(point t) {	//x ascending, then y ascending
		return x < t.x or (x == t.x and y == t.y);
	}
} p[maxn];	//point set
int id[maxn], n;

bool cmpY(int i, int j) {	//make y ascending(subscript needed) 
	
	return p[i].y < p[j].y;
}
double len(int i, int j) {	//length between 2 points
	
	return sqrt(pow(p[i].x - p[j].x, 2) + pow(p[i].y - p[j].y, 2));
}
double closestPair(int l, int r) {
	
	if (l == r) return INT_MAX;
	if (l + 1 == r) return len(l, r);
	//calculate closestPairs of 2 subsets
	int m = (l + r) / 2, d1 = closestPair(l, m), d2 = closestPair(m + 1, r), ct = 0;
	double d = min(d1, d2);
	for (int i = l; i <= r; i++) {	//1st optimize: choose points whose distance from midpoint < d
		if (abs(p[i].x - p[m].x) <= d) id[ct++] = i;
	}
	sort(id, id + ct, cmpY);
	for (int i = 0; i < ct; i++) {	//2nd optimize: if the distance on Y-axis >= d, then break
		for (int j = i + 1; j < ct and p[id[j]].y - p[id[i]].y < d; j++) {
			d = min(d, len(id[i], id[j]));
		}
	}
	return d;
}
void closestPairTest() {	//test function
	
//	cin >> n;
//    for (int i = 0; i < n; i++) {
//    	cin >> p[i].x >> p[i].y;
//	}
	const int data[] = {0, 0, 0, 1, 1, 0, 1, 1, 2, 2, 2, 3, 3, 2, 3, 3};
	n = 8;
	for (int i = 0, id = 0; i < n; i++) {
		p[i].x = data[id++];
		p[i].y = data[id++];
	}
	
	sort(p, p + n);
	printf("%.2lf\n", closestPair(0, n - 1));
}


/********* main ********/
int main(){
	
	chessBoardTest();
	findKTest();
	closestPairTest();
	
    return 0;
}








