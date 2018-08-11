#include <bits/stdc++.h>
using namespace std;
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
inline int val(char ctmp){
  if(isdigit(ctmp)) return ctmp-'0';
  return ctmp-'A'+10;
}
const int N=101010;
const int D=16;
const int BS=1021;
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
struct Nd{
  int v[D];
} st[N<<2];
int R[D][D];
Nd operator+(const Nd& lret, const Nd& rret){
  Nd ret;
  for(int i=0; i<D; i++) ret.v[i]=0;
  for(int i=0; i<D; i++)
    for(int j=0; j<D; j++){
      int to=R[i][j];
      //int to=(i+j)%(D-1);
      //if(to==0 and i+j>0) to=D-1;
      ret.v[to]=add(ret.v[to], mul(lret.v[i], rret.v[j]));
    }
  return ret;
}
int n, q, bs[D];
char c[N];
void build_st(int no, int l, int r){
  if(l == r){
    for(int i=0; i<D; i++) st[no].v[i]=0;
    st[no].v[0]++;
    st[no].v[val(c[l])]++;
    return;
  }
  build_st(L(no), l, mid);
  build_st(R(no), mid+1, r);
  st[no]=st[L(no)]+st[R(no)];
}
void modify(int no, int l, int r, int p, int v){
  if(l == r){
    for(int i=0; i<D; i++) st[no].v[i]=0;
    st[no].v[0]++;
    st[no].v[v]++;
    return;
  }
  if(p<=mid) modify(L(no), l, mid, p, v);
  else modify(R(no), mid+1, r, p, v);
  st[no]=st[L(no)]+st[R(no)];
}
Nd query(int no, int l, int r, int ql, int qr){
  if(l==ql and r==qr) return st[no];
  if(qr<=mid) return query(L(no), l, mid, ql, qr);
  if(mid<ql) return query(R(no), mid+1, r, ql, qr);
  return query(L(no), l, mid, ql, mid)+
         query(R(no), mid+1, r, mid+1, qr);
}
inline int query(int ql, int qr){
  Nd ret=query(1, 1, n, ql, qr);
  ret.v[0]=sub(ret.v[0], 1);
  int ans=0;
  for(int i=0; i<D; i++)
    ans=add(ans, mul(bs[i], ret.v[i]));
  return ans;
}
int main(){
  bs[0]=1;
  for(int i=1; i<D; i++)
    bs[i]=mul(bs[i-1], BS);
  for(int i=0; i<D; i++)
    for(int j=0; j<D; j++){
      int to=(i+j)%(D-1);
      if(to == 0 and i+j>0) to=D-1;
      R[i][j]=to;
    }
  scanf("%d%d", &n, &q);
  scanf("%s", c+1);
  build_st(1, 1, n);
  while(q--){
    int cmd; scanf("%d", &cmd);
    if(cmd == 1){
      int p; char tmp[D];
      scanf("%d%s", &p, tmp);
      modify(1, 1, n, p, val(tmp[0]));
    }else{
      int ql, qr;
      scanf("%d%d", &ql, &qr);
      printf("%d\n", query(ql, qr));
    }
  }
}
