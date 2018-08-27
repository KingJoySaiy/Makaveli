#include <bits/stdc++.h>
using namespace std;
const int N=101010;
int myrand(){
  int ret=0;
  for(int i=0; i<2; i++)
    ret=(ret<<15)|(rand()&((1<<15)-1));
  return ret;
}
struct Treap{
	int sz , val , pri;
	Treap *l , *r;
	Treap( int _val ){
		val = _val; sz = 1;
		pri = myrand(); l = r = NULL;
	}
};
int Size( Treap * a ){ return a ? a->sz : 0; }
void pull( Treap * a ){
	a->sz = Size( a->l ) + Size( a->r ) + 1;
}
Treap* merge( Treap *a , Treap *b ){
	if( !a || !b ) return a ? a : b;
	if( a->pri > b->pri ){
		a->r = merge( a->r , b );
		pull( a );
		return a;
	}else{
		b->l = merge( a , b->l );
		pull( b );
		return b;
	}
}
void split( Treap *t , int k , Treap*&a , Treap*&b ){
	if( !t ){ a = b = NULL; return; }
	if( Size( t->l ) + 1 <= k ){
		a = t;
		split( t->r , k - Size( t->l ) - 1 , a->r , b );
		pull( a );
	}else{
		b = t;
		split( t->l , k , a , b->l );
		pull( b );
	}
}
int n, m, p, s, ans[N], ptr;
Treap *t, *tl, *tr;
void go(Treap* now){
  if(!now) return;
  go(now->l);
  ans[ptr++]=now->val;
  go(now->r);
}
int main(){
  scanf("%d%d", &n, &m);
  t=NULL;
  for(int i=1; i<=n; i++)
    t=merge(t, new Treap(i));
  while(m--){
    scanf("%d%d", &p, &s);
    split(t, p-1, tl, t);
    split(t, s, t, tr);
    t=merge(t, tl);
    t=merge(t, tr);
  }
  go(t);
  for(int i=0; i<n; i++)
    printf("%d%c", ans[i], " \n"[i+1==n]);
}
