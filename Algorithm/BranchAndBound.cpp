#include <bits/stdc++.h>

using namespace std;

const int maxn = 105;
const int inf = INT_MAX / 2;

/******** shortest path Dijstra ********/
struct data {
	int to, cost;
	data(int x, int y) : to(x), cost(y) {}
	bool operator < (const data &t) const {
		return cost > t.cost;
	}
}; 
void Dijkstra(vector<data> a[], int n, int x, int res[]) {	//start from x
	
	fill(res, res + maxn, inf);	//initiate result
	res[x] = 0;
	priority_queue<data> que;
	que.push(data(x, 0));	//initiate priority queue, the cost to x is 0
	while (!que.empty()) {
		data t = que.top(); que.pop();	//get the top of the priority queue
		if (t.cost > res[t.to]) continue;	//if the cost already bigger than res, then dismiss it
		for (auto &p : a[t.to]) {
			if (res[p.to] > res[t.to] + p.cost) {	//t as the transfer node, try to relax edges & push it into the priority queue
				res[p.to] = res[t.to] + p.cost;
				que.push(data(p.to, res[p.to]));
			}
		}
	}
}
void DijkstraTest() {	//test function
	
	const int aa[][3] = {{2, 4, 2}, {1, 4, 3}, {7, 2, 2}, {3, 4, 3}, {5, 7, 5}, 
	{7, 3, 3}, {6, 1, 1}, {6, 3, 4}, {2, 4, 3}, {5, 6, 3}, {7, 2, 1}};	//initial data
	int n = 7, m = 11, begin = 5;
	vector<data> a[maxn];	//adjaceny table, a[i]=data(j, k) means exist an edge between i & j costing k
	for (int i = 0; i < m; i++) {
		a[aa[i][0]].push_back(data(aa[i][1], aa[i][2]));
		a[aa[i][1]].push_back(data(aa[i][0], aa[i][2]));
	}
	
	int res[maxn];
	Dijkstra(a, n, begin, res);
	cout << "shortest path from " << begin << ": ";
	for (int i = 1; i <= n; i++) {
		cout << res[i] << ' ';
	}
	cout << endl;
}


/******** main ********/
int main() {
	
	DijkstraTest();
	
	return 0;
}
