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

struct Combi
{
	vector<int> fact;
	vector<int> ifact;
	vector<int> inv;
	vector<int> pow3;
	const int MOD = (1e9 + 7);
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
	int choose(int a, int b)
	{
		if(a<b) return 0;
		if(b==0) return 1;
		if(a==b) return 1;
		return mult(fact[a],mult(ifact[b],ifact[a-b]));
	}
	int inverse(int a)
	{
		return modpow(a,MOD-2);
	}
	void init(int _n)
	{
		fact.clear(); ifact.clear(); inv.clear(); pow3.clear();
		fact.resize(_n+1);
		ifact.resize(_n+1);
		inv.resize(_n+1);
		pow3.resize(_n+1);
		pow3[0]=1;
		ifact[0]=1;
		fact[0]=1;
		for(int i=1;i<=_n;i++)
		{
			pow3[i]=mult(pow3[i-1],3);
			fact[i]=mult(fact[i-1],i);
			//ifact[i]=mult(ifact[i-1],inv[i]);
		}
		ifact[_n] = inverse(fact[_n]);
		for(int i=_n-1;i>=1;i--)
		{
		    ifact[i] = mult(ifact[i + 1], i + 1);
		}
		for(int i=1;i<=_n;i++)
		{
		    inv[i] = mult(fact[i-1],ifact[i]);
		}
	}
};

Combi combi;

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	combi.init(1011111);
	int n; cin>>n;
	int ans = 0;
	for(int d=1;d<=n;d++)
	{
		int total = 0;
		for(int k=2;k<=n/d+1;k++) //choose k elements
		{
			int remaining = n + d - 1 - k*d;
			if(remaining<0) continue;
			total = add(total, combi.choose(k+remaining,k));
		}
		//total = # of ways to choose >= 2 elements
		int summax = 0;
		for(int k=2;(k-1)*d<=n-1;k++) //choose k elements
		{
			int N = n - 1 - (k-1)*(d-1);
			int sum = add(mult(n+1,combi.choose(N+1,k)), MOD - combi.choose(N+2,k+1));
			summax = add(summax, sum);
		}
		int summin = add(mult(n+1, total), MOD - summax);
		ans = add(ans, add(summax, MOD - summin));
	}
	cout<<ans<<'\n';
}
