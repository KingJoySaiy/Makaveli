#include <bits/stdc++.h>
using namespace std;
const int N=10000010;
int p[N];
bool np[N];
int main(){
  for(int i=2; i<N; i++) if(not np[i]){
    p[i]=1;
    for(int j=i; j<N; j+=i) np[j]=true;
  }
  for(int i=1; i<N; i++) p[i]+=p[i-1];
  int n; cin>>n;
  long long ans=0;
  for(int i=1; i<=n; i++)
    ans+=(long long)p[n/i]*(p[n/i]-1);
  cout<<ans<<endl;
}
