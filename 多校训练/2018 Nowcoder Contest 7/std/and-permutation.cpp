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

vi solve(int n)
{
	if(n==0) return {};
	int k=0;
	while((1<<(k+1))<=n) k++;
	vi perm(n);
	for(int i=0;i<(1<<k);i++) perm[i]=(1<<k)-1-i;
	for(int i=0;i<n-(1<<k);i++) perm[(1<<k)-1-i]^=(1<<k);
	vi tmp = solve(n-(1<<k));
	for(int i=(1<<k);i<n;i++) perm[i]=tmp[i-(1<<k)];
	return perm;
}
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n; cin>>n;
	vi perm = solve(n);
	for(int i=0;i<n;i++)
	{
		cout<<perm[i];
		if(i+1<n) cout<<' ';
	}
	cout<<'\n';
}
