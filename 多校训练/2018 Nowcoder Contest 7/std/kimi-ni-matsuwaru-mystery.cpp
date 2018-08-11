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

struct node
{
	ll a[3];
};

struct cmp {
    bool operator()(const node &a, const node& b) const {
        if(a.a[0]!=b.a[0]) return a.a[0]<b.a[0];
        if(a.a[1]!=b.a[1]) return a.a[1]<b.a[1];
        return a.a[2]<b.a[2];
    }
};

node combine(node x, node y)
{
	node z;
	for(int i=0;i<3;i++)
	{
		z.a[i] = (x.a[i]+x.a[(i+1)%3])*(y.a[i]+y.a[(i+1)%3]) - x.a[(i+1)%3]*y.a[(i+1)%3];
	}
	return z;
}

node create(ll a, ll b, ll c)
{
	node tmp;
	tmp.a[0]=a; tmp.a[1]=b; tmp.a[2]=c;
	return tmp;
}

bool equal(node x, node y)
{
	for(int i=0;i<3;i++) {if(x.a[i]!=y.a[i]){return false;}}
	return true;
}

map<node,string,cmp> ma[6];

void gen_possibilities()
{
	ma[0][create(1,0,0)]="R";
	ma[0][create(0,1,0)]="S";
	ma[0][create(0,0,1)]="P";
	ma[0][create(1,1,1)]="?";
	for(int i=1;i<=4;i++)
	{
		for(auto it = ma[i-1].begin(); it != ma[i-1].end(); it++)
		{
			for(auto it2 = ma[i-1].begin(); it2 != ma[i-1].end(); it2++)
			{
				ma[i][combine(it->fi,it2->fi)] = it->se+it2->se;
			}
		}
	}
}

set<ll> S;

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin>>t;
	gen_possibilities();
	ll cur = 1;
	for(int i=0;i<=32;i++)
	{
		S.insert(cur); cur*=3;
	}
	while(t--)
	{
		node A;
		for(int i=0;i<3;i++) cin>>A.a[i];
		ll sum = A.a[0]+A.a[1]+A.a[2];
		if(S.find(sum)==S.end())
		{
			cout<<"Impossible\n"; continue;
		}
		bool pos=0;
		for(int i=0;i<=4;i++)
		{
			if(ma[i].find(A)!=ma[i].end())
			{
				cout<<ma[i][A]<<'\n'; pos=1;
				break;
			}
		}
		if(pos) continue;
		for(auto it = ma[4].begin(); it != ma[4].end(); it++)
		{
			node cur = it->fi;
			ll sumsmall = cur.a[0]+cur.a[1]+cur.a[2];
			if(sum<sumsmall) continue;
			if(pos) break;
			ll bsum = sum/sumsmall;
			if(cur.a[0]!=0&&cur.a[1]!=0&&cur.a[2]!=0)
			{
				node B;
				for(int i=0;i<3;i++)
				{
					ld RHS = (ld(A.a[i])/ld(cur.a[i]))*ld(cur.a[(i+1)%3]+cur.a[(i+2)%3]) + (ld(A.a[(i+2)%3])/ld(cur.a[i]+cur.a[(i+2)%3]))*ld(cur.a[(i+1)%3]) - A.a[(i+1)%3];
					ld LHS = (ld(cur.a[i]+cur.a[(i+1)%3])/ld(cur.a[i]))*ld(cur.a[(i+1)%3]+cur.a[(i+2)%3]) + (ld(cur.a[(i+2)%3])/ld(cur.a[i]+cur.a[(i+2)%3]))*ld(cur.a[(i+1)%3]);
					B.a[i] = floor(RHS/LHS);
				}
				ll sum = B.a[0]+B.a[1]+B.a[2];
				for(ll x = -1; x <= 1; x++)
				{
					for(ll y = -1; y <= 1; y++)
					{
						for(ll z = -1; z <= 1; z++)
						{
							if(S.find(sum+x+y+z)!=S.end())
							{
								node tmp = create(B.a[0]+x, B.a[1]+y, B.a[2]+z);
								if(ma[4].find(tmp)!=ma[4].end())
								{
									if(equal(combine(cur, tmp),A))
									{
										cout<<it->se+ma[4][tmp]<<'\n';
										pos=1;
									}
								}
							}
							if(pos) break;
						}
						if(pos) break;
					}
					if(pos) break;
				}
			}
			else
			{
				for(int i=0;i<3;i++)
				{
					if(cur.a[i]==0)
					{
						if(cur.a[(i+1)%3]==0||cur.a[(i+2)%3]==0) //cannot have 2 0s
						{
							break;
						}
						else
						{
							node B;
							B.a[i] = A.a[i]/cur.a[(i+1)%3];
							B.a[(i+2)%3] = A.a[(i+2)%3]/cur.a[(i+2)%3] - B.a[i];
							B.a[(i+1)%3] = bsum - B.a[i] - B.a[(i+2)%3];
							if(equal(combine(cur,B),A))
							{
								if(ma[4].find(B)!=ma[4].end())
								{
									cout<<it->se+ma[4][B]<<'\n';
									pos=1; break;
								}
							}
						}
					}
				}
			}
		}
		if(!pos) cout<<"Impossible\n";
	}
}
