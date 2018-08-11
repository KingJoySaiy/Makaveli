// @author peter50216
// lots of default code (especially dump/R/W) borrowed from shik, thanks!
// #includes {{{
#include <bits/stdc++.h>
using namespace std;
// }}}
// {{{ custom namespace, to avoid name collision.
// stupid macro so that vim doesn't get one more indent...
#define MYSPACE namespace zone_of_peter50216{
#define MYSPACE_END }

MYSPACE
// }}}
// #defines & template magics {{{
#define SZ(x) ((int)(x).size())
#define ALL(x) begin(x), end(x)
#define REP(i,n) for (int i=0; i<(n); i++ )
#define REP1(i,a,b) for (int i=(a); i<=(b); i++ )
#define PER(i,n) for (int i=(n)-1; i>=0; i--)
#define PER1(i,a,b) for (int i=(a); i>=(b); i--)
#define FOR(it,c) for (auto it=(c).begin(); it!=(c).end(); it++)
#define MS0(x) memset(x,0,sizeof(x))
#define MS1(x) memset(x,-1,sizeof(x))
#define SEP(x) ((x)?'\n':' ')
using namespace std;
typedef int64_t LL;
typedef uint64_t ULL;
typedef pair<int,int> PII;
typedef vector<int> VI;

#ifdef SHIK
template<typename T>
void _dump( const char* s, T&& head ) { cerr<<s<<"="<<head<<endl; }

template<typename T, typename... Args>
void _dump( const char* s, T&& head, Args&&... tail ) {
  int c=0;
  while ( *s!=',' || c!=0 ) {
    if ( *s=='(' || *s=='[' || *s=='{' ) c++;
    if ( *s==')' || *s==']' || *s=='}' ) c--;
    cerr<<*s++;
  }
  cerr<<"="<<head<<", ";
  _dump(s+1,tail...);
}

#define dump(...) do { \
  fprintf(stderr, "%s:%d - ", __PRETTY_FUNCTION__, __LINE__); \
  _dump(#__VA_ARGS__, __VA_ARGS__); \
} while (0)

template<typename Iter>
ostream& _out( ostream &s, Iter b, Iter e ) {
  s<<"[";
  for ( auto it=b; it!=e; it++ ) s<<(it==b?"":" ")<<*it;
  s<<"]";
  return s;
}

template<typename A, typename B>
ostream& operator <<( ostream &s, const pair<A,B> &p ) { return s<<"("<<p.first<<","<<p.second<<")"; }
template<typename T>
ostream& operator <<( ostream &s, const vector<T> &c ) { return _out(s,ALL(c)); }
template<typename T, size_t N>
ostream& operator <<( ostream &s, const array<T,N> &c ) { return _out(s,ALL(c)); }
template<typename T>
ostream& operator <<( ostream &s, const set<T> &c ) { return _out(s,ALL(c)); }
template<typename A, typename B>
ostream& operator <<( ostream &s, const map<A,B> &c ) { return _out(s,ALL(c)); }
#else
#define dump(...)
#endif

template<typename T>
void _R( T &x ) { cin>>x; }
void _R( int &x ) { scanf("%d",&x); }
void _R( int64_t &x ) { scanf("%" PRId64,&x); }
void _R( double &x ) { scanf("%lf",&x); }
void _R( char &x ) { scanf(" %c",&x); }
void _R( char *x ) { scanf("%s",x); }
template<typename T>
void _R( vector<T>& v ) {
  size_t s; scanf("%zu", &s);
  v.resize(s);
  for (size_t i = 0; i < s; i++) _R(v[i]);
}

void R() {}
template<typename T, typename... U>
void R( T& head, U&... tail ) {
  _R(head);
  R(tail...);
}

#define DRI(...) int __VA_ARGS__; R(__VA_ARGS__)
#define CASET int t; R(t); for(int cas=1; cas<=t; cas++)

template<typename T>
void _W( const T &x ) { cout<<x; }
void _W( const int &x ) { printf("%d",x); }
template<typename T>
void _W( const vector<T> &x ) {
  for ( auto i=x.cbegin(); i!=x.cend(); i++ ) {
    if ( i!=x.cbegin() ) putchar(' ');
    _W(*i);
  }
}

void W() {}
template<typename T, typename... U>
void W( const T& head, const U&... tail ) {
  _W(head);
  putchar(sizeof...(tail)?' ':'\n');
  W(tail...);
}

inline string ssprintf(const char* format, ...) {
  static char buf[1000000]; // who cares about buffer overflow :P
  va_list args;
  va_start(args, format);
  vsprintf(buf, format, args);
  va_end(args);
  return buf;
}

// }}}

const int P=958922753,root=3,MAXNUM=524288;
// Remember coefficient are mod P
/*
   p=a*2^n+1
    n        2^n          p   a   root
    5         32         97   3      5
    6         64        193   3      5
    7        128        257   2      3
    8        256        257   1      3
    9        512       7681  15     17
   10       1024      12289  12     11
   11       2048      12289   6     11
   12       4096      12289   3     11
   13       8192      40961   5      3
   14      16384      65537   4      3
   15      32768      65537   2      3
   16      65536      65537   1      3
   17     131072     786433   6     10
   18     262144     786433   3     10  (605028353, 2308, 3)
   19     524288    5767169  11      3
   20    1048576    7340033   7      3
   21    2097152   23068673  11      3
   22    4194304  104857601  25      3
   23    8388608  167772161  20      3
   24   16777216  167772161  10      3
   25   33554432  167772161   5      3  (1107296257, 33, 10)
   26   67108864  469762049   7      3
   27  134217728 2013265921  15     31
   */
inline LL bigmod(long long a,int b){
   if(b==0)return 1;
   return (bigmod((a*a)%P,b/2)*(b%2?a:1ll))%P;
}
inline int inv(int a,int b){
   if(a==1)return 1;
   return (((long long)(a-inv(b%a,a))*b+1)/a)%b;
}
std::vector<long long> ps(MAXNUM);
std::vector<int> rev(MAXNUM);
struct poly{
   std::vector<unsigned int> co;
   int n;//polynomial degree = n
   poly(int d){n=d;co.resize(n+1,0);}
   void trans2(int NN){
      int r=0,st,N;
      unsigned int a,b;
      while((1<<r)<(NN>>1))++r;
      for(N=2;N<=NN;N<<=1,--r){
         for(st=0;st<NN;st+=N){
            int i,ss=st+(N>>1);
            for(i=(N>>1)-1;i>=0;--i){
               a=co[st+i]; b=(ps[i<<r]*co[ss+i])%P;
               co[st+i]=a+b; if(co[st+i]>=P)co[st+i]-=P;
               co[ss+i]=a+P-b; if(co[ss+i]>=P)co[ss+i]-=P;
            }
         }
      }
   }
   void trans1(int NN){
      int r=0,st,N;
      unsigned int a,b;
      for(N=NN;N>1;N>>=1,++r){
         for(st=0;st<NN;st+=N){
            int i,ss=st+(N>>1);
            for(i=(N>>1)-1;i>=0;--i){
               a=co[st+i]; b=co[ss+i];
               co[st+i]=a+b; if(co[st+i]>=P)co[st+i]-=P;
               co[ss+i]=((a+P-b)*ps[i<<r])%P;
            }
         }
      }
   }
   poly operator*(const poly& _b)const{
      poly a=*this,b=_b;
      int k=n+b.n,i,N=1;
      while(N<=k)N*=2;
      a.co.resize(N,0); b.co.resize(N,0);
      int r=bigmod(root,(P-1)/N),Ni=inv(N,P);
      ps[0]=1;
      for(i=1;i<N;++i)ps[i]=(ps[i-1]*r)%P;
      a.trans1(N);b.trans1(N);
      for(i=0;i<N;++i)a.co[i]=((long long)a.co[i]*b.co[i])%P;
      r=inv(r,P);
      for(i=1;i<N/2;++i)std::swap(ps[i],ps[N-i]);
      a.trans2(N);
      for(i=0;i<N;++i)a.co[i]=((long long)a.co[i]*Ni)%P;
      a.n=n+_b.n; return a;
   }
};

char s[260000],t[260000];
int ss[260000];
int sl,tl;
int m(int x){
  x%=P;
  if(x<0)x+=P;
  return x;
}
int add(int x,int y){
  x+=y;
  if(x>=P)x-=P;
  return x;
}
void ff(LL(*f1)(LL), LL(*f2)(LL)){
  poly p1(sl-1),p2(tl-1);
  REP(i,sl)p1.co[i]=m(f1(s[i]));
  REP(i,tl)p2.co[i]=m(f2(t[i]));
  poly v=p1*p2;
  REP(i,tl-sl+1)ss[i]=add(ss[i],v.co[i+sl-1]);
}

int tmp[260000];
char per[30];

int main(int argc, char* argv[]) {
  R(s,t);
  sl=strlen(s),tl=strlen(t);
  assert(1<=sl&&sl<=tl&&tl<=250000);
  REP(i,sl)assert('a'<=s[i]&&s[i]<='z');
  REP(i,tl)assert('a'<=t[i]&&t[i]<='z');

  scanf("%s", per);

  for(int i=0; i<sl; i++) s[i]=per[s[i]-'a'];
  for(int i=0; i<tl; i++) t[i]=per[t[i]-'a'];


  // (x-y)^2((x-y)^2-1)
  for(int i=0,j=sl-1;i<j;i++,j--)swap(s[i],s[j]);
  {
    // ff([](int x){return bigmod(x, 4);}, [](int){return 1;});
    int s0=0;
    REP(i,sl)s0=add(s0,bigmod(s[i],4));
    REP(i,tl-sl+1)ss[i]=add(ss[i],s0);
  }
  // dump(VI(ss,ss+tl));
  ff([](LL x){return bigmod(x, 3);}, [](LL y){return -4*y;});
  // dump(VI(ss,ss+tl));
  ff([](LL x){return bigmod(x, 2);}, [](LL y){return 6*bigmod(y, 2)-1;});
  // dump(VI(ss,ss+tl));
  ff([](LL x){return x;}, [](LL y){return -4*bigmod(y,3)+2*y;});
  // dump(VI(ss,ss+tl));
  {
    // ff([](int){return 1;}, [](int y){return bigmod(y,4)-bigmod(y,2);});
    auto f2=[](LL y){return bigmod(y,4)-bigmod(y,2);};
    REP(i,tl)tmp[i]=m(f2(t[i]));
    int s=0;
    REP(i,sl)s=add(s,tmp[i]);
    REP(i,tl-sl+1){
      ss[i]=add(ss[i],s);
      s-=tmp[i];if(s<0)s+=P;
      if(i+sl<tl)s=add(s,tmp[i+sl]);
    }
  }
  VI ans;
  // dump(VI(ss,ss+tl));
  REP(i,tl-sl+1)if(ss[i]==0)ans.push_back(i+1);
  W(SZ(ans));
  if(SZ(ans))W(ans);
  return 0;
}

// {{{ END
MYSPACE_END
int main(int argc, char* argv[]) { return zone_of_peter50216::main(argc,argv); }
// }}}
// vim: fdm=marker:commentstring=\ \"\ %s:nowrap:autoread

