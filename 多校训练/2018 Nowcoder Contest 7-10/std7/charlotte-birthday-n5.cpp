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

const int MOD = 1e9 + 7;

int add(int a, int b)
{
	a+=b;
	while(a>=MOD) a-=MOD;
	return a;
}

int mult(int a, int b)
{
	return (a*1LL*b)%MOD;
}

int modpow(int a, int b)
{	
	int r=1;
	while(b)
	{
		if(b&1) r=mult(r,a);
		a=mult(a,a);
		b>>=1;
	}
	return r;	
}

const int N = 40;
int C[N+5][N+5];
int fact[N+5];
int ifact[N+5];
int pow2[N+5];

int choose(int n, int r)
{	
	if(n<0||r<0) return 0;
	if(n<r) return 0;
	if(C[n][r]!=-1) return C[n][r];
	if(r==0) return (C[n][r]=1);	
	return (C[n][r] = add(choose(n-1,r), choose(n-1,r-1)));
}

int dp[N+5][N+5][N+5][2*N+5];
int dp2[N+5][N+5][N+5][N+5]; //# of cols, # of rows considered, # of used >=2 columns, # of used once columns; each row has exactly 1 bit, stores # of such grids 
int dp3[N+5][N+5][N+5]; //# of >= 2 rows, # of >= 2 cols, # of = 1 cols
int dp4[N+5][N+5][N+5][N+5]; //m, i, n1, k
int dp5[N+5][N+5][N+5]; //m, n1, rem

int solve(int n, int m, int n1, int lvl) //n rows, m cols, n1 rows with = 1 X, each col has >= 2 X, lvl layers left to unravel, no rows and cols are empty
{
	if(n<=0||m<=0) return 0;
	if(dp[n][m][n1][lvl]!=-1) return dp[n][m][n1][lvl];
	if(lvl==0) 
	{
		if(n1==0) return (dp[n][m][n1][lvl]=0);
		int coeff = mult(m*n1, choose(n,n1));
		int ans = 0;
		for(int i=0;i<=m;i++)
		{
			for(int j=0;i+j<=m;j++)
			{
				if(dp3[n-n1][i][j]!=0)
				{
					int v = dp3[n-n1][i][j];
					int rem = m - i;
					//n1 - 1 rows left, m - 1 columns
					//we must have at least rem bits placed in the last n1 rows
					int coeff3 = mult(choose(m-1, i+j-1), fact[i+j-1]);
					int sum = 0;
					if(n1==1)
					{
						if(rem==0) sum = 1;
					}
					else
					{
						sum = dp5[m][n1][rem];
					}
					ans = add(ans, mult(v, mult(coeff3, sum)));
				}
			}
		}
		ans = mult(ans, coeff);
		return (dp[n][m][n1][lvl] = ans);
	}
	int ans = 0; int coeff = choose(n,n1);
	for(int i = 0; i <= m; i++)
	{
		int v = solve(m, n - n1, i, lvl-1);
		//there are i 1s, how many ways are there to choose the positions of the n1 ones?
		ans = add(ans, mult(v, dp4[m][i][n1][i]));
	}
	ans = mult(ans, coeff);
	return (dp[n][m][n1][lvl] = ans);
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	memset(C,-1,sizeof(C));
	fact[0]=1; for(int i=1;i<=N;i++) fact[i]=mult(fact[i-1],i);
	ifact[0]=1;	for(int i=1;i<=N;i++) ifact[i]=modpow(fact[i],MOD-2);
	pow2[0]=1; for(int i=1;i<=N;i++) pow2[i]=add(pow2[i-1],pow2[i-1]);
	
	for(int i=1;i<=N;i++) dp2[i][1][0][1] = i;
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=N;j++)
		{
			for(int k=0;k<=N;k++)
			{
				for(int l=0;l<=N;l++)
				{
					if(dp2[i][j][k][l]!=0)
					{
						int v=dp2[i][j][k][l];
						dp2[i][j+1][k][l] = add(dp2[i][j+1][k][l], mult(k, v));
						if(l>=1) dp2[i][j+1][k+1][l-1] = add(dp2[i][j+1][k+1][l-1], mult(l, v));
						if(k+l+1<=i) dp2[i][j+1][k][l+1] = add(dp2[i][j+1][k][l+1], mult(i - k - l, v));
					}
				}
			}
		}
	}

	dp3[0][0][1] = 1; //later we multiply by m*n1 in the solve function. here we assume the answer bit is alrdy taken once
	for(int rows=0;rows<N;rows++)
	{
		for(int j=0;j<=N;j++) //2-bits
		{
			for(int k=0;k+j<=N;k++) //1-bits
			{
				if(dp3[rows][j][k]==0) continue;
				int v=dp3[rows][j][k];
				for(int l=0;l<=k;l++) //change L of the 1-bits to 2-bits
				{
					for(int z=0;z+j+k<=N;z++) //change z of the 0-bits to 1-bits
					{
						int coeff = 1;
						if(l+z>=2)
						{
							coeff = mult(pow2[j], mult(choose(k, l), ifact[z]));
						}
						else if(l+z==1)
						{
							coeff = mult(add(pow2[j], MOD - 1), mult(choose(k, l), ifact[z]));
						}
						else
						{
							coeff = add(pow2[j], MOD - j - 1); //choose any subset of those
						}
						dp3[rows+1][j+l][k+z-l] = add(dp3[rows+1][j+l][k+z-l], mult(coeff, v));
					}
				}
			}
		}
	}
	for(int m = 1; m <= N; m++) //given m columns, i from recursive function, how many ways to assign the remaining 1s for the last n1 rows?
	{
		for(int i = 0; i <= m; i++)
		{
			dp4[m][i][0][0] = 1;
			for(int j = 1; j <= N; j++)
			{
				for(int k = 0; k <= i; k++)
				{
					dp4[m][i][j][k] = mult(dp4[m][i][j-1][k], m - (i - k));
					if(j>0) dp4[m][i][j][k] = add(dp4[m][i][j][k], mult(dp4[m][i][j-1][k-1], i - k + 1));
				}
			}
		}
	}
	for(int m = 1; m <= N; m++) 
	{
		for(int n1 = 1; n1 <= N; n1++)
		{
			for(int rem = 0; rem <= N; rem++)
			{
				for(int k = rem; k <= m - 1; k++)
				{
					int coeff2 = choose(m - 1 - rem, k - rem);
					dp5[m][n1][rem] = add(dp5[m][n1][rem], mult(coeff2, dp2[k][n1-1][k][0]));
				}
			}
		}
	}
	int nn,m,lvl; cin>>nn>>m>>lvl;
	memset(dp,-1,sizeof(dp));
	int ans = 0;
	for(int n = 1; n <= nn; n++)
	{
		int coeffultimate = choose(nn,n);
		int ans2 = 0;
		for(int n1 = 0; n1 < n; n1++)
		{
			int coeff = choose(n, n1);
			int sum = 0;
			for(int empty = 0; empty <= m; empty++)
			{
				int coeff2 = mult(choose(m, empty), modpow(m, n1));
				int sum2 = 0;
				for(int k = 0; k <= m - empty; k++)
				{
					sum2 = add(sum2, solve(m - empty, n - n1, k, 2*lvl - 1));
				}
				sum = add(sum, mult(sum2, coeff2));
			}
			ans2 = add(ans2, mult(coeff, sum));
		}
		ans = add(ans, mult(coeffultimate, ans2));
	}
	cout<<ans<<'\n';
}
