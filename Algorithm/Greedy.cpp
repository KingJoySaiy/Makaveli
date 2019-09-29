#include <bits/stdc++.h>

using namespace std;

const int maxn = 105;
const int inf = INT_MAX / 2;

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


/******** best load ********/ 
void selectSort(int a[], int n, int id[]) {
	
	for (int i = 0; i < n; i++) {
		id[i] = i;
	}
	for (int i = 0, res; i < n; i++) {
		res = i;
		for (int j = i + 1; j < n; j++) {
			if (a[res] > a[j]) res = j;
		}
		swap(a[res], a[i]);
		swap(id[res], id[i]);
	} 
}
int bestLoad(int a[], int n, int all, bool select[]) {
	
	int id[n], ct = 0;
	selectSort(a, n, id);
	memset(select, 0, sizeof(0));
	for (int i = 0; i < n; i++) {
		if (all >= a[i]) {
			all -= a[i];
			select[id[i]] = true;
			ct++;
		}
	}
	return ct;
}
void bestLoadTest() {
	
	int a[] = {20, 10, 26, 15, 9, 18}, n = 6, all = 70;
	bool select[maxn] = {};
	printf("maximum nunber of loads: %d\n", bestLoad(a, n, all, select));
	for (int i = 0; i < n; i++) {
		cout << select[i] << ' ';
	}
	cout << endl;
}


/******** shortest path Dijstra ********/ 
void Dijkstra(int cost[][maxn], int n, int x, int res[]) {	//start from x
	
	bool book[maxn] = {};		//mark whether used
	book[x] = true;
	for (int i = 1; i <= n; i++) {	//initialization
		res[i] = cost[x][i];
	}
	
	for (int i = 1; i < n; i++) {
		int now = inf;
		for (int j = 1; j <= n; j++) {
			if (!book[j] and res[j] < now) {
				now = res[j];
				x = j;
			}
		}
		book[x] = true;	//find x that is unmarked & has shortest res, then update res
		for (int j = 1; j <= n; j++) {
			res[j] = min(res[j], res[x] + cost[x][j]);
		}
	}
}
void DijsktraTest() {
	
	int a[][3] = {{2, 4, 2}, {1, 4, 3}, {7, 2, 2}, {3, 4, 3}, {5, 7, 5}, 
	{7, 3, 3}, {6, 1, 1}, {6, 3, 4}, {2, 4, 3}, {5, 6, 3}, {7, 2, 1}};	//initial data
	int cost[maxn][maxn], n = 7, m = 11, begin = 5;
	for (int i = 0; i < maxn; i++) {	//initialize adjacency list
		fill(cost[i], cost[i] + maxn, inf);
		cost[i][i] = 0;
	}
	for (int i = 0; i < m; i++) {	//cost[from][to] = Cost
		cost[a[i][0]][a[i][1]] = a[i][2];
	}
	
	int res[maxn];
	Dijstra(cost, n, begin, res);
	cout << "shortest path from " << begin << ": ";
	for (int i = 1; i <= n; i++) {
		cout << res[i] << ' ';
	}
	cout << endl;
}

/******** main ********/ 
int main() {

	partialPackageTest();
	bestLoadTest();
	DijstraTest();

    return 0;
}

