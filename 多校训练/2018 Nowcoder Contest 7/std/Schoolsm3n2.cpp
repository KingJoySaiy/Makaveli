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
typedef double ld; 
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> pbds;
typedef set<ll>::iterator sit;
typedef map<ll,ll>::iterator mit;

const int M = 31;
const int N = 251;
vector<ii> intervals;
ld sum[N+1];

ld getsum(int l, int r)
{
	if(l==0) return sum[r];
	else return sum[r]-sum[l-1];
}
ld dp[M+1][N+1][N+1];
int lastvisit2[M+1][N+1][N+1];
pair<ld,int> nxtl[M+1][M+1][N+1];
pair<ld,int> nxtr[M+1][M+1][N+1];
ii curseg;
vector<pair<ii,int> > intervals2;
int curvisit2;
ld calc2(int n, int cur, int L, int R) //cur = current interval, [L,R] ppl left
{
	int lef=L; int ri=R;
	if(lef>ri) return -ld(1e18);
	if(lastvisit2[cur][L][R]!=curvisit2) 
	{
		dp[cur][L][R]=-ld(1e10)-1;
	}
	if(dp[cur][L][R]>=-ld(1e10)) return dp[cur][L][R];
	lastvisit2[cur][L][R] = curvisit2;
	int l = intervals[cur].fi; int r = intervals[cur].se;
	vi vec;
	for(int i = 0; i < intervals.size(); i++)
	{
		int l2 = intervals[i].fi; int r2 = intervals[i].se;
		if(l2>l)
		{
			if(r2<r)
			{
				vec.pb(i);
			}
		}
	}
	//vec contains the set of segments inside
	if(vec.empty()&&R-L+1>=curseg.fi&&R-L+1<=curseg.se) 
	{
		return (dp[cur][L][R] = getsum(lef,ri)/ld(ri-lef+1));
	}
	ld ans = -ld(1e9);
	//all left
	{
		int lef = L; int ri = R; int ext = 0;
		vi LE;
		for(int cur:vec)
		{
			ext+=intervals[cur].fi; LE.pb(intervals[cur].fi);
		}				
		int middlel = curseg.fi; int middler = curseg.se;
		if(ext+middlel<=ri-lef+1&&ri-lef+1<=ext+middler)
		{
			sort(LE.begin(),LE.end()); LE.pb(ri-lef+1-ext);
			ld tot = 0;
			for(int x:LE)
			{
				tot += getsum(lef, lef+x-1)/ld(x); lef+=x;
			}
			ans = max(ans, tot);
		}				
	}
	for(int v:vec)
	{
		lef=L; ri=R;
		ld tot = nxtl[cur][v][lef].fi; lef = nxtl[cur][v][lef].se;
		tot += nxtr[cur][v][ri].fi; ri = nxtr[cur][v][ri].se;
		//cerr<<cur<<' '<<v<<' '<<lef<<' '<<ri<<'\n';
		tot += calc2(n, v, lef, ri);
		ans = max(ans, tot);
	}
	return (dp[cur][L][R] = ans);
}


ld solve_m3n2(vector<ll> students, vector<ii> schools)
{
	sort(students.rbegin(),students.rend());
	int n = students.size(); int m = schools.size();
	vector<ld> S(n);
	S[0] = students[0];
	for(int i=1;i<n;i++)
	{
		S[i] = students[i]+S[i-1];
	}
	for(int j=0;j<m;j++)
	{
		for(int k=0;k<=n;k++)
		{
			for(int l=0;l<=n;l++)
			{
				lastvisit2[j][k][l]=-1;
			}
		}
	}
	for(int i=0;i<n;i++) sum[i]=S[i];
	ld ans = 0;
	for(int i=0;i<m;i++)
	{
		vector<ii> vec;
		for(int j=0;j<m;j++)
		{
			if(j==i) continue;
			vec.pb(schools[j]);
		}
		curvisit2 = i;
		intervals = vec;
		curseg = schools[i];
		sort(intervals.begin(),intervals.end());
		for(int j=0;j<intervals.size();j++)
		{
			vi vec;
			int L = intervals[j].fi; int R = intervals[j].se;
			for(int k = 0; k < intervals.size(); k++)
			{
				int l2 = intervals[k].fi; int r2 = intervals[k].se;
				if(l2>L)
				{
					if(r2<R)
					{
						vec.pb(k);
					}
				}
			}
			for(int v:vec)
			{
				int l = intervals[v].fi; int r = intervals[v].se;
				int lef = 0; int ri = 0;
				int ext = 0; int ext2 = 0;
				vi LE; vi RI;
				for(int k:vec)
				{
					int l2 = intervals[k].fi; int r2 = intervals[k].se;
					if(l2<l)
					{
						LE.pb(l2);
						ext+=l2; 
					}
					else if(l2==l)
					{
						if(r2<r)
						{
							LE.pb(l2);
							ext+=l2;
						}
						else if(r2==r)
						{
							if(k<v) 
							{
								ext+=l2; LE.pb(l2);
							}
							else 
							{
								ext2+=r2; RI.pb(r2);
							}
						}
						else
						{
							RI.pb(r2); ext2+=r2;
						}
					}
					else
					{
						if(r2>=r)
						{
							RI.pb(r2); ext2+=r2;
						}
					}
				}
				sort(RI.rbegin(),RI.rend());
				for(int l=0;l<n;l++)
				{
					ld tot = 0;
					lef = l;
					if(lef+ext>=n)
					{
						lef = n;
					}
					else
					{
						for(int x:LE)
						{
							tot += getsum(lef, lef+x-1)/ld(x); lef+=x;
						}
					}
					nxtl[j][v][l] = mp(tot, lef);
				}
				for(int r=n-1;r>=0;r--)
				{
					ld tot = 0;
					ri = r;
					if(ri-ext2+1<0)
					{
						ri = -1;
					}
					else
					{
						for(int x:RI)
						{
							tot += getsum(ri-x+1, ri)/ld(x); ri -= x;
						}
					}
					//cerr<<j<<' '<<v<<' '<<r<<' '<<tot<<' '<<ri<<'\n';
					nxtr[j][v][r] = mp(tot, ri);
				}
			}
		}
		//all choose left somehow
		{
			int lef = 0; int ext = 0;
			vi LE;
			for(int cur=0;cur<intervals.size();cur++)
			{
				ext+=intervals[cur].fi; LE.pb(intervals[cur].fi);
			}				
			if(ext+curseg.fi<=n&&ext+curseg.se>=n)
			{
				sort(LE.begin(),LE.end()); LE.pb(n-ext);
				ld tot = 0;
				for(int x:LE)
				{
					tot += getsum(lef, lef+x-1)/ld(x); lef+=x;
				}
				ans = max(ans, tot);
			}				
		}
		for(int cur=0;cur<intervals.size();cur++)
		{
			int l = intervals[cur].fi; int r = intervals[cur].se;
			int lef = 0; int ri = n - 1; int ext = 0;
			vi LE,RI;
			for(int j = 0; j < intervals.size(); j++)
			{
				int l2 = intervals[j].fi; int r2 = intervals[j].se;
				if(l2<l)
				{
					LE.pb(l2);
					ext+=l2; 
				}
				else if(l2==l)
				{
					if(r2<r)
					{
						LE.pb(l2);
						ext+=l2;
					}
					else if(r2==r)
					{
						if(j<cur) 
						{
							ext+=l2; LE.pb(l2);
						}
						else 
						{
							ext+=r2; RI.pb(r2);
						}
					}
					else
					{
						RI.pb(r2); ext+=r2;
					}
				}
				else
				{
					if(r2>=r)
					{
						RI.pb(r2); ext+=r2;
					}
				}
			}
			ld tot = 0;
			sort(RI.rbegin(),RI.rend());
			for(int x:LE)
			{
				tot += getsum(lef, lef+x-1)/ld(x); lef+=x;
			}
			for(int x:RI)
			{
				tot += getsum(ri-x+1, ri)/ld(x); ri -= x;
			}
			tot += calc2(n, cur, lef, ri);
			ans = max(ans, tot);
			//cerr<<i<<' '<<cur<<' '<<lef<<' '<<ri<<' '<<tot<<'\n';
		}
		//cerr<<"CASES : "<<i<<' '<<cases<<'\n';
	}
	return ans;
}

vector<ll> st;
vector<ii> sc;

void read_case()
{
	st.clear(); sc.clear();
	int n; cin>>n;
	for(int i=0;i<n;i++)
	{
		int x; cin>>x; st.pb(x);
	}
	int m; cin>>m;
	int sum=0;
	for(int i=0;i<m;i++)
	{
		int l,r; cin>>l>>r; sc.pb(mp(l,r)); 
		assert(l<=r);
		sum+=r;
	}
	assert(sum>=n);
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	read_case();
	cout<<fixed<<setprecision(10)<<solve_m3n2(st,sc)<<'\n';
}
