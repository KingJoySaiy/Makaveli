#include <bits/stdc++.h>

using namespace std;

const int maxn = 105;
const int inf = INT_MAX / 2;

/******** max flow *********/
struct data1 {	//edge tructure
	int to, cap, rev;	//to, capture, id of the reverse edge
	data1(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {}
};
void add1(vector<data1> a[], int from, int to, int cap) {	//add edge
	
	a[from].push_back(data1(to, cap, a[to].size()));
	a[to].push_back(data1(from, 0, a[from].size() - 1));
}
int dfs(vector<data1> a[], bool book[maxn], int st, int ed, int f) {	//find augmented road 
	
	if(st == ed) return f;
	book[st] = true;
	for (auto &e : a[st]) {
		if (!book[e.to] and e.cap > 0) {
			int d = dfs(a, book, e.to, ed, min(f, e.cap));
			if (d > 0) {	//find a transfer case from e.to to ed
				e.cap -= d;
				a[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;	//impossible to transfer flow from st to ed
}
int maxFlow(vector<data1> a[], int st, int ed) {	//calculate the maximum flow from st to ed
	 
	bool book[maxn];	//mark whether used
	int flow = 0, tmp;
	while (true) {
		memset(book, 0, sizeof(book));
		if ((tmp = dfs(a, book, st, ed, inf)) == 0) return flow;
		flow += tmp;
	}
}
void maxFlowTest() {	//test function
	
	const int tt[] = {0, 1, 10, 0, 2, 2, 1, 2, 6, 1, 3, 6, 2, 4, 5, 3, 2, 3, 3, 4, 8};
	vector<data1> a[maxn];	//adjacency table
	int st = 0, ed = 4;
	for (int i = 0; i < 21; i += 3) {
		add1(a, tt[i], tt[i + 1], tt[i + 2]);
	}
	printf("max flow result: %d\n", maxFlow(a, st, ed));
}


/******** min cost flow ********/ 
struct data2 {	//edge structure
	int to, cap, cost, rev;		//to, capture, cost, id of the reverse edge
	data2(int to, int cap, int cost, int rev) : to(to), cap(cap), cost(cost), rev(rev) {}
};

void add2(vector<data2> a[], int from, int to, int cap, int cost) {	//add edge
	
	a[from].push_back(data2(to, cap, cost, a[to].size()));
	a[to].push_back(data2(from, 0, -cost, a[from].size() - 1));
}
int minCostFlow(vector<data2> a[], int n, int flow, int st, int ed) {	//calculate the minimum cost of the flow from st to ed  
	
	int dis[maxn], res = 0;
	int preId[maxn], preE[maxn];	//the id of the pre vertex & edge
	
	while (flow > 0) {	//loop until flow == 0
		fill(dis, dis + maxn, inf);
		dis[st] = 0;
		bool update = true;
		while (update) {	//Bellman-Ford algorithm
			update = false;
			for (int v = 0; v < n; v++) {
				if (dis[v] == inf) continue;
				for (int i = 0; i < a[v].size(); i++) {
					auto &e = a[v][i];
					if (e.cap > 0 and dis[e.to] > dis[v] + e.cost) {
						dis[e.to] = dis[v] + e.cost;
						preId[e.to] = v;	//mark pre id & edge 
						preE[e.to] = i;
						update = true;
					}
				}
			}
		}
		if (dis[ed] == inf) return -1;
		int d = flow;	//find the possible flow
		for (int i = ed; i != st; i = preId[i]) {
			d = min(d, a[preId[i]][preE[i]].cap);
		}
		flow -= d;
		
		res += d * dis[ed];	//update result & cap
		for (int i = ed; i != st; i = preId[i]) {
			auto &e = a[preId[i]][preE[i]];
			e.cap -= d;
			a[i][e.rev].cap += d;
		}
	}
	return res;
} 
void minCostFlowTest() {	//test function
	
	const int tt[] = {0, 1, 10, 2, 0, 2, 2, 4, 1, 2, 6, 6, 1, 3, 6, 2,
			 2, 4, 5, 2, 3, 2, 3, 3, 3, 4, 8, 6};
	int n = 5, st = 0, ed = 4;
	vector<data2> a[maxn];	//adjacency table
	for (int i = 0; i < 28; i += 4) {
		add2(a, tt[i], tt[i + 1], tt[i + 2], tt[i + 3]);
	}
	printf("min cost flow result: %d\n", minCostFlow(a, n, 5, st, ed));
}

/******** main ********/
int main() {
	
	maxFlowTest();
	minCostFlowTest();
	
	return 0;
}















