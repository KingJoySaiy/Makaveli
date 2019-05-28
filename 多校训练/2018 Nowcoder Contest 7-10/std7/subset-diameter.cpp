#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define fbo find_by_order
#define ook order_of_key
 
typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef long double ld; 
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> pbds;
typedef set<ll>::iterator sit;
typedef map<ll,ll>::iterator mit;

const int N = 100010;
vi adj[N];
int n;
const int MOD=1e9+7;

int add(int a, int b)
{
	a+=b; while(a>=MOD) a-=MOD;
	return a;
}

int mult(int a, int b)
{
	return (a*1LL*b)%MOD;
}

int pow2[N];

void read()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++) adj[i].clear();
	for(int i=0;i<n-1;i++)
	{
		int u,v; scanf("%d %d",&u,&v); u--; v--;
		adj[u].pb(v); adj[v].pb(u);
	}
}

vi res[N];
deque<int> *dp[N];
int subsize[N];
bool globalvisited[N];
int shift[N];
int par[N];

void calcsiz(int u, int p)
{
	subsize[u]=1; par[u]=p;
	for(int v:adj[u])
	{
		if(v==p) continue;
		calcsiz(v,u);
		subsize[u]+=subsize[v];
	}
}

void dfs(int u, int p, vi &require)
{
	int mx = -1; int bigchild = -1;
	for(int v:adj[u])
	{
		if(v!=p&&subsize[v]>mx)
		{
			mx=subsize[v];
			bigchild=v;
		}
	}
	for(int v:adj[u])
	{
		if(v!=p) dfs(v,u,require);
	}
	if(bigchild==-1)
	{
		dp[u] = new deque<int>();
		dp[u]->pb(1); shift[u] = 0;
	}
	else
	{
		dp[u] = dp[bigchild]; shift[u] = shift[bigchild]; shift[u]++;
		dp[u]->push_front(1-shift[u]);
		for(int v:adj[u])
		{
			if(v!=p&&v!=bigchild)
			{
				if(dp[v]->size()>=dp[u]->size())
				{
					int X = dp[u]->back()+shift[u];
					int ptr = 1;
					for(int k:*dp[v])
					{
						if(ptr<int(dp[u]->size()))
						{
							dp[u]->at(ptr)+=(k+shift[v]);
						}
						else
						{
							dp[u]->pb(X+k+shift[v]-shift[u]); //check
						}
						ptr++;
					}
				}
				else
				{
					int ext = dp[v]->back()+shift[v];
					shift[u]+=dp[v]->back()+shift[v];
					dp[u]->at(0)-=ext;
					int ptr=1;
					for(int k:*dp[v])
					{
						assert(ptr<int(dp[u]->size()));
						dp[u]->at(ptr)-=(ext-(k+shift[v]));
						ptr++;
					}
				}
			}
		}
	}
	for(int x:require)
	{
		if(x<0) res[u].pb(0);
		else if(x<dp[u]->size()) res[u].pb(dp[u]->at(x)+shift[u]); 
		else res[u].pb(dp[u]->back()+shift[u]);
	}
}

int ans[N];
int siz[N];

void compsiz(int u, int p)
{
	siz[u]=1;
	for(int v:adj[u])
	{
		if(v==p||globalvisited[v]) continue;
		compsiz(v,u);
		siz[u]+=siz[v];
	}
}

int centroid(int u, int p, int rt)
{
	for(int v:adj[u])
	{
		if(v==p||globalvisited[v]) continue;
		if(siz[v]*2>=siz[rt])
		{
			return centroid(v,u,rt);
		}
	}
	return u;
}

vector<vi> children;
int h[N];
int sum[N];
int maxh;
void dfs_inner(int u, int p, int hh, int D)
{
	h[u] = hh; children.back().pb(u); maxh=max(maxh,hh);
	for(int v:adj[u])
	{
		if(globalvisited[v]||v==p) continue;
		dfs_inner(v,u,hh+1,D);
	}
}

void push(int u, int p, int tot, int id)
{
	if(tot==0) return ; //nothing to push
	ans[u]+=tot;
	for(int v:adj[u])
	{
		if(globalvisited[v]||v==p) continue;
		push(v,u,tot-sum[id],id+1);
	}
}

void solve_root(int u, int D)
{
	children.clear();
	h[u] = 0; sum[D]=0; maxh=0;
	for(int v:adj[u])
	{
		if(globalvisited[v]) continue;
		children.pb(vi());
		dfs_inner(v, u, 1, D);
	}
	int cur = 0;
	sum[D]++; cur++;
	for(int i=0;i<children.size();i++)
	{
		for(int j:children[i])
		{
			if(D-h[j]>=0) 
			{
				sum[D-h[j]]++; cur++;
			}
		}
	}
	ans[u] += cur;
	int ptr=0;
	for(int v:adj[u])
	{
		if(globalvisited[v]) continue;
		for(int j:children[ptr])
		{
			if(D-h[j]>=0)
			{
				sum[D-h[j]]--; cur--;
			}
		}
		push(v, u, cur-sum[0], 1);
		for(int j:children[ptr])
		{
			if(D-h[j]>=0)
			{
				sum[D-h[j]]++; cur++;
			}
		}
		ptr++;
	}
	for(int i=D;i>=max(0,D-maxh);i--) sum[i]=0;
}

void solve_all(int u, int D)
{
	if(D<0) return ;
	compsiz(u,-1);
	int cent = centroid(u,-1,u);
	solve_root(cent,D);
	globalvisited[cent]=1;
	for(int v:adj[cent])
	{
		if(!globalvisited[v])
		{
			solve_all(v,D);
		}
	}
}

int solve_fast(int D)
{
	//clear
	for(int i=0;i<n;i++)
	{
		res[i].clear();
	}
	calcsiz(0,-1);	
	if(D%2==0)
	{
		vi req = {D/2-2,D/2-1,D/2};
		dfs(0,-1,req);
		vi alldist;
		solve_all(0,D/2-1);
		for(int i=0;i<n;i++)
		{
			alldist.pb(ans[i]); ans[i]=0; globalvisited[i]=0;
		}
		vi alldist2;
		solve_all(0,D/2);
		for(int i=0;i<n;i++)
		{
			alldist2.pb(ans[i]); ans[i]=0; globalvisited[i]=0;
		}
		int ans = 0;
		for(int i=0;i<n;i++)
		{
			int coeff = pow2[alldist[i]];
			vi C; int S=0;
			for(int v:adj[i])
			{
				if(v==par[i]) continue;
				C.pb(res[v][1]-res[v][0]); S+=res[v][1]-res[v][0];
			}
			if(par[i]>=0)
			{
				C.pb((alldist2[i]-alldist[i])-S);
			}
			S = alldist2[i] - alldist[i];
			int cnt = add(pow2[S],MOD-1);
			for(int v:C)
			{
				cnt = add(cnt, MOD+1-pow2[v]);
			}
			ans = add(ans, mult(cnt,coeff));
		}
		return ans;
	}
	else
	{
		vi req = {D/2-2,D/2-1,D/2};
		dfs(0,-1,req);
		vi alldist;
		solve_all(0,D/2-1);
		for(int i=0;i<n;i++)
		{
			alldist.pb(ans[i]); ans[i]=0; globalvisited[i]=0;
		}
		vi alldist2;
		solve_all(0,D/2);
		for(int i=0;i<n;i++)
		{
			alldist2.pb(ans[i]); ans[i]=0; globalvisited[i]=0;
		}
		int ans = 0;
		for(int u=0;u<n;u++)
		{
			for(int v:adj[u])
			{
				if(u==par[v])
				{
					int coeff = pow2[res[v][1]+alldist[u]-res[v][0]];
					int R = res[v][2]-res[v][1];
					int L = alldist2[u]-alldist[u]-(res[v][1]-res[v][0]);
					int cnt = add(add(pow2[L+R],MOD-1),add(MOD-add(pow2[L],MOD-1),MOD-add(pow2[R],MOD-1)));
					ans = add(ans, mult(cnt,coeff));
				}
			}
		}
		return ans;
	}
}

int main()
{
	pow2[0]=1;
	for(int i=1;i<N;i++) pow2[i]=add(pow2[i-1],pow2[i-1]);
	read(); int D; scanf("%d",&D);
	int ans_fast = solve_fast(D);
	printf("%d\n", ans_fast);
	return 0;
}
