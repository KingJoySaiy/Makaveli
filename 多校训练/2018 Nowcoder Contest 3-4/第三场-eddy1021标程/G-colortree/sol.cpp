#include <bits/stdc++.h>
using namespace std;
const int N=5140;
const int mod=1000000007;
inline int add(int a, int b){
  a+=b;
  return a>=mod?a-mod:a;
}
inline int sub(int a, int b){
  a-=b;
  return a<0?a+mod:a;
}
inline int mul(long long a, int b){
  a*=b;
  return a>=mod?a%mod:a;
}
inline int mpow(int a, int b){
  int r=1;
  while(b){
    if(b&1) r=mul(r, a);
    a=mul(a, a);
    b>>=1;
  }
  return r;
}
int n, k, d, inq[N], tg[N], stmp;
vector<int> v[N];
int go(int now, int prt, int dep){
  if(tg[now] != stmp) return 0;
  int ret=1;
  if(dep == 0) return ret;
  for(int son: v[now]){
    if(son == prt) continue;
    ret+=go(son, now, dep-1);
  }
  return ret;
}
int f(int g){
  if(g == 0) return mpow(k, n);
  ++ stmp;
  queue<int> Q;
  Q.push(1);
  inq[1]=stmp;
  int way=1;
  while(Q.size()){
    int tn=Q.front(); Q.pop();
    tg[tn]=stmp;
    int cnt=go(tn, tn, g)-1;
    if(cnt>=k) return 0;
    way=mul(way, k-cnt);
    for(int other: v[tn])
      if(inq[other] != stmp){
        Q.push(other);
        inq[other]=stmp;
      }
  }
  return way;
}
int main(){
  scanf("%d%d%d", &n, &k, &d);
  for(int i=1; i<n; i++){
    int ui, vi;
    scanf("%d%d", &ui, &vi);
    v[ui].push_back(vi);
    v[vi].push_back(ui);
  }
  printf("%d\n", sub(f(d-1), f(d)));
}
