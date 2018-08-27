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
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> pbds;
typedef set<ll>::iterator sit;
typedef map<ll,ll>::iterator mit;

bool B[22][(1<<20)+5];
int ans = 0;
int dp[5][(1<<16)+15];

void gen(int n)
{
	int pow3=1;
	for(int i=0;i<n;i++) pow3*=3;
	for(int i=0;i<(1<<(1<<n));i++)
	{
		for(int k=0;k<(1<<n);k++)
		{
			if(i&(1<<k)) B[n][k] = 1;
			else B[n][k] = 0;
		}
		for(int j=0;j<pow3;j++)
		{
			int cur = j;
			for(int k=n-1;k>=0;k--)
			{
				int z=cur%3;
				for(int l=0;l<(1<<k);l++)
				{
					if(z==0) B[k][l]=B[k+1][2*l]&B[k+1][2*l+1];
					else if(z==1) B[k][l]=B[k+1][2*l]^B[k+1][2*l+1];
					else B[k][l]=B[k+1][2*l]|B[k+1][2*l+1];
				}
				cur/=3;
			}
			dp[n][i] += B[0][0];
		}
	}
}

void solve(int n)
{
	if(n<=4)
	{
		int bit = 0;
		for(int i=0;i<(1<<n);i++)
		{
			if(B[n][i]) bit^=(1<<i);
		}
		ans += dp[n][bit];
		return ;
	}
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < (1<<(n-1)); j++)
		{
			if(i==0) B[n-1][j] = B[n][2*j]&B[n][2*j+1];
			else if(i==1) B[n-1][j] = B[n][2*j]^B[n][2*j+1];
			else B[n-1][j] = B[n][2*j]|B[n][2*j+1];
		}
		solve(n-1);
	}
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n; cin>>n; string z; cin>>z;
	for(int i=0;i<=4;i++) gen(i);
	for(int i=0;i<(1<<n);i++)
	{
		B[n][i] = z[i] - '0';
	}
	solve(n);
	cout<<ans<<'\n';
}
