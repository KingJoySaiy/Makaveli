#ifndef INC_233_UNIONFIND_H
#define INC_233_UNIONFIND_H

class UnionFind {	//union-find-set
private:
	int *fa, *rank;
public:
	UnionFind(int n) {	//constructor
		fa = new int[n];
		rank = new int[n];
		for (int i = 0; i <= n; i++) {
			fa[i] = i;
			rank[i] = 1;
		}
	} 
	~UnionFind() {	//destructor
		delete fa;
		delete rank;
	}
	int find(int x) {	//find father-node of x
		if (fa[x] == x) return x;
		return fa[x] = find(fa[x]);
	}
	bool same(int x, int y) {	//check whether x & y located in the same set
		return find(x) == find(y);
	}
	void Union(int x, int y) {	//union x-node & y-node
		x = find(x);
		y = find(y);
		if (rank[x] < rank[y]) fa[x] = y;
		else {
			fa[y] = x;
			if (rank[x] == rank[y]) rank[x]++;
		}
	}
};

#endif //INC_233_UNIONFIND_H
