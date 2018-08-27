#include <bits/stdc++.h>
using namespace std;
const int N=5140;
const int mod=1000000007;
int fac[N], ifac[N];
int add(int a, int b){
  a+=b;
  return a>=mod?a-mod:a;
}
int sub(int a, int b){
  a-=b;
  return a<0?a+mod:a;
}
int mul(long long a, int b){
  a*=b;
  return a>=mod?a%mod:a;
}
int mpow(int a, int b){
  int ret=1;
  while(b){
    if(b&1) ret=mul(ret,a);
    a=mul(a,a);
    b>>=1;
  }
  return ret;
}
int inv(int x){
  return mpow(x, mod-2);
}
void build(){
  fac[0]=ifac[0]=1;
  for(int i=1; i<N; i++){
    fac[i]=mul(fac[i-1], i);
    ifac[i]=inv(fac[i]);
  }
}
inline int C(int a, int b){
  if(a<b) return 0;
  return mul(fac[a], mul(ifac[b], ifac[a-b]));
}
int n, par[N];
vector<int> v[N];
void gen(const vector<int>& vv){
  assert(vv.size()>2u);
  for(size_t i=0; i<vv.size(); i++)
    for(size_t j=i+1; j<vv.size(); j++)
      par[vv[i]+vv[j]]=sub(par[vv[i]+vv[j]], 1);
  if(vv.size()>2u){
    for(size_t i=0; i<vv.size(); i++)
      par[vv[i]]=add(par[vv[i]], vv.size()-2u);
  }
}
int go(int now, int prt){
  int cnt=1;
  vector<int> other;
  for(int son: v[now]){
    if(son == prt) continue;
    int scnt=go(son, now);
    other.push_back(scnt);
    cnt+=scnt;
  }
  if(cnt<n) other.push_back(n-cnt);
  if(v[now].size()>2u)
    gen(other);
  return cnt;
}
int main(){
  build();
  scanf("%d", &n);
  for(int i=1; i<n; i++){
    int ui, vi;
    scanf("%d%d", &ui, &vi);
    v[ui].push_back(vi);
    v[vi].push_back(ui);
  }
  go(1, 1);
  int deg12=0;
  for(int i=1; i<=n; i++)
    if(v[i].size()<=2u)
      deg12++;
  for(int i=1; i<=n; i++){
    int tot=mul(deg12, C(n-1,i-1));
    tot=add(tot, mul(n-deg12, C(n, i)));
    for(int j=i; j<=n; j++)
      tot=add(tot, mul(par[j], C(j, i)));
    tot=mul(tot, inv(C(n, i)));
    printf("%d\n", tot);
  }
}
