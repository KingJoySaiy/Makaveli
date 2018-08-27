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
typedef pair<ll,ll> ii;
typedef vector<int> vi;
typedef long double ld; 
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;
typedef set<int>::iterator sit;
typedef map<int,int>::iterator mit;
typedef vector<int>::iterator vit;

vector<ii> edges;
int n;

void add(int u, int v)
{
	edges.pb(mp(u,v));
}

ll ncr(int n, int k)
{
	if(n<k) return 0;
	ll ans = 1;
	for(int i = n; i >= n - k + 1; i--)
	{
		ans*=i;
	}
	for(int i = 1; i <= k; i++) ans/=i;
	return ans;
}

const int N = 200001;

int iv[200001];
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	memset(iv,-1,sizeof(iv));
	for(int i=1;i<=100;i++) iv[ncr(i,3)]=i;
	int z; cin>>z;
	n=4;
	int C = 70;
	while(n<C&&ncr(n+1,4)<z)
	{
		n++;
	}
	C = min(C, n);
	z -= ncr(n,4);
	vi res;
	for(int i = 2; i <= C; i++)
	{
		for(int j = i; j <= C; j++)
		{
			for(int k = j; k <= C; k++)
			{
				for(int l = k; l <= C; l++)
				{
					int cnt = ncr(i,3)+ncr(j,3)+ncr(k,3)+ncr(l,3);
					if(cnt<=z&&iv[z-cnt]>=0&&iv[z-cnt]<=C)
					{
						res.pb(i);res.pb(j);res.pb(k);res.pb(l);res.pb(iv[z-cnt]);
					}
					if(!res.empty()) break;
				}
				if(!res.empty()) break;
			}
			if(!res.empty()) break;
		}
		if(!res.empty()) break;
	}
	assert(!res.empty());
	for(int i = 1; i <= n; i++)
	{
		for(int j = i + 1; j <= n; j++)
		{
			add(i,j);
		}
	}
	for(int i = n + 1; i <= n + 5; i++)
	{
		for(int j = 0; j < res[i-n-1]; j++)
		{
			add(i,j+1);
		}
	}	
	n+=5;
	cout<<n<<' '<<edges.size()<<'\n';
	for(int i = 0; i < edges.size(); i++)
	{
		cout<<edges[i].fi<<' '<<edges[i].se<<'\n';
	}
}

