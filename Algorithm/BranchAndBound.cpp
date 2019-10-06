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


/******** loading problem 2 ********/
struct loadNode {	//binary tree
	loadNode *parent;
	int id, sum;	//current height & sum
	bool ok;	//whether select id
	loadNode(loadNode *parent, int id, int sum, bool ok) : parent(parent), id(id), sum(sum), ok(ok) {}
};
void loading2(int c1, int c2, int n, int w[]) {	//load n package to 2 ships(maximum weights of them are c1 & c2)
	
	loadNode *p[1 << (n + 1)] = {new loadNode(nullptr, -1, 0, false)};	//temporary pointer array 
	queue<loadNode*> que;	//initialize the queue
	que.push(p[0]);
	bool select[maxn] = {};
	int sum1 = 0, sum2 = 0, bestSum1 = 0, ct = 1;
	
	while (!que.empty()) {
		loadNode *t = que.front(); que.pop();	//get the front of queue & pop it
		if (t->id != n - 1) {
			if (t->sum + w[t->id + 1] <= c1) {	//try to load id to 1st ship
				p[ct++] = new loadNode(t, t->id + 1, t->sum + w[t->id + 1], true);
				que.push(p[ct - 1]);
			}
			p[ct++] = new loadNode(t, t->id + 1, t->sum, false);	//dismiss id
			que.push(p[ct - 1]);
		} else if (t->sum > bestSum1) {	//if 1st ship could load more, then update result
				bestSum1 = t->sum;
				while (t->id != -1) {
					select[t->id] = t->ok;
					t = t->parent;
				}
		}
	}
	for (int i = 0; i < ct; i++) {	//free all pointer safely 
		delete p[i];
	}
	for (int i = 0; i < n; i++) {
		select[i] ? (sum1 += w[i]) : (sum2 += w[i]);
	}
	printf("load-weight of the 2 ships: %d, %d\nship number of each package: ", sum1, sum2);
	for (int i = 0; i < n; i++) {
		printf("%d%c", select[i] ? 1 : 2, " \n"[i == n - 1]);
	}
} 
void loading2Test() {	//test function
	
	int c1 = 55, c2 = 35, n = 4, w[] = {20, 15, 30, 20};
	loading2(c1, c2, n, w);
}


/******** 0-1 package ********/
int weight[maxn], value[maxn];

struct pacNode {	//binary tree
	pacNode *parent;
	int id, sumW, sumV;		//current height, sumWeight & sumValue
	bool ok;	//whether select id
	pacNode(pacNode *parent, int id, int sumW, int sumV, bool ok) : parent(parent), id(id), sumW(sumW), sumV(sumV), ok(ok) {}
//	bool operator < (const pacNode &t) const {		//overload operator '<' (needed when use priority_queue) 
//		return value[id] * weight[t.id] < value[t.id] * weight[id];
//	}
};
void package(int n, int all) {
	
	int select[maxn] = {}, len = 0, maxValue = -inf, ct = 1;
	pacNode *p[1 << (n + 1)] = {new pacNode(nullptr, -1, 0, 0, false)};	//temporary pointer array 
//	priority_queue<pacNode*> que;	//my perspective: not necessary to use priority_queue, because all of the 2^(n+1)-1 pacNodes must be used
	queue<pacNode*> que;	//initialize the queue
	que.push(p[0]);
	
	while (!que.empty()) {
		pacNode *t = que.front(); que.pop();	//get the front of queue & pop it
		if (t->id != n - 1) {
			if (t->sumW + weight[t->id + 1] <= all) {	//try to select id
				p[ct++] = new pacNode(t, t->id + 1, t->sumW + weight[t->id + 1], t->sumV + value[t->id + 1], true);
				que.push(p[ct - 1]);
			}
			p[ct++] = new pacNode(t, t->id + 1, t->sumW, t->sumV, false);	//dismiss id
			que.push(p[ct - 1]);
		} else if (t->sumV > maxValue) {	//if 1st ship could load more, then update result
				maxValue = t->sumV;
				len = 0;
				while (t->id != -1) {
					if (t->ok) select[len++] = t->id;
					t = t->parent;
				}
		}
	}
	for (int i = 0; i < ct; i++) {	//free all pointer safely 
		delete p[i];
	}
	cout << "max value of the 0-1 package: " << maxValue << "\nselected id of the packages: ";
	for (int i = len - 1; ~i; i--) {
		cout << select[i] << " \n"[!i];
	}
}
void packageTest() {	//test function
	
	int w[] = {2, 1, 3, 2}, v[] = {3, 2, 4, 2};
	int n = 4, all = 5;
	for (int i = 0; i < n; i++) {
		weight[i] = w[i];
		value[i] = v[i];
	}
	package(n, all);
}


/******** main ********/
int main() {
	
	DijkstraTest();
	loading2Test();
	packageTest(); 

	
	return 0;
}
