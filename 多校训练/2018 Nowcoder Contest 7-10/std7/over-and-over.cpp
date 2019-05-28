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

int a[2111][2111];
int R[2111][2111];
int D[2111][2111];

int convert(char c)
{
	if(c>='a'&&c<='z') return c-'a';
	else return c-'A'+26;
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n,m; cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			char c; cin>>c; a[i][j]=convert(c);
		}
	}
	for(int i = 0; i < n; i++)
	{
		ll curbit = 0; int ptr = -1;
		for(int j = 0; j < m; j++)
		{
			while(ptr+1<m&&!(curbit&(1LL<<a[i][ptr+1])))
			{
				ptr++;
				curbit|=(1LL<<a[i][ptr]);
			}
			R[i][j] = ptr;
			curbit^=(1LL<<a[i][j]);
		}
	}
	for(int j = 0; j < m; j++)
	{
		int ptr = -1; ll curbit = 0; 
		for(int i = 0; i < n; i++)
		{			
			while(ptr+1<n&&!(curbit&(1LL<<a[ptr+1][j])))
			{
				ptr++;
				curbit|=(1LL<<a[ptr][j]);
			}
			D[i][j] = ptr;
			curbit^=(1LL<<a[i][j]);
		}
	}
	ll ans = 0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			//count number of sudoku grids with top-left corner (i,j)
			int ptr = min(j+52, m - 1);
			vi vec(53,-1);
			for(int k=j;k<min(j+53,m);k++)
			{
				vec[k-j] = D[i][k];
				if(k>j) vec[k-j]=min(vec[k-j],vec[k-1-j]);
			}
			for(int k=i;k<n;k++)
			{
				if(ptr<j) break;
				while(ptr>=j&&(R[k][j]<ptr||vec[ptr-j]<k)) ptr--;
				ans+=ptr-j+1;
			}
		}
	}
	cout<<ans<<'\n';
}
