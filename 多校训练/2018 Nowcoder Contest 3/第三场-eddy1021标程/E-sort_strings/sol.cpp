#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline int add(int a, int b, int mod){
  a+=b;
  return a>=mod?a-mod:a;
}
inline int sub(int a, int b, int mod){
  a-=b;
  return a<0?a+mod:a;
}
inline int mul(LL a, int b, int mod){
  a*=b;
  return a>=mod?a%mod:a;
}
const int N=(1<<20);
const int K=3;
const int mods[K]={1000000007, 1000000009, 1010102101};
const int _BS=13131;
struct Int{
  int vl[K];
  Int(int v=0){
    for(int i=0; i<K; i++)
      vl[i]=v%mods[i];
  }
  Int operator+(const Int& he) const{
    Int ret;
    for(int i=0; i<K; i++)
      ret.vl[i]=add(vl[i], he.vl[i], mods[i]);
    return ret;
  }
  Int operator-(const Int& he) const{
    Int ret;
    for(int i=0; i<K; i++)
      ret.vl[i]=sub(vl[i], he.vl[i], mods[i]);
    return ret;
  }
  Int operator*(const Int& he) const{
    Int ret;
    for(int i=0; i<K; i++)
      ret.vl[i]=mul(vl[i], he.vl[i], mods[i]);
    return ret;
  }
  pair<LL,LL> to_pll() const{
    return {vl[0]*(LL)mods[1]+vl[1], vl[2]};
  }
};
char c[N];
Int BS(_BS);
map<pair<LL,LL>, int> id;
vector<int> ans;
vector<int> v[N];
int main(){
  scanf("%s", c);
  int len=strlen(c);
  Int dbs=Int(1);
  for(int i=0; i<len; i++) dbs=dbs*BS;
  Int cur;
  for(int i=0; i<len+len-1; i++){
    cur=cur*BS+Int(c[i%len]);
    if(i-len>=0) cur=cur-dbs*Int(c[i-len]);
    if(i>=len-1){
      int idx=i-(len-1);
      pair<LL,LL> p=cur.to_pll();
      if(id.find(p) == id.end()){
        ans.push_back(idx);
        id[p]=idx;
      }
      v[id[p]].push_back(idx);
    }
  }
  printf("%d\n", (int)ans.size());
  for(int idx: ans){
    printf("%d", (int)v[idx].size());
    for(int i: v[idx]) printf(" %d", i);
    puts("");
  }
}
