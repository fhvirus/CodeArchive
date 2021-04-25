#pragma Ofast
#pragma loop-opt(on)
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'||c>'9');a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=' ';if(OP>65524)write(1,OB,OP),OP=0;}
inline char Rc(){
	static char c;
	while((c = RC()) != 'R' and c != 'S');
	return c;
}
#include<algorithm>
using namespace std;

const int N = 130000 + 225;
int n, m;

/* Start Treap */
int val[N], l[N], r[N], sz[N], cnt = 1;
unsigned pri[N];
bool tag[N];
inline unsigned ran(){
	static unsigned x = 131;
	return ++(x *= 0xdefaced);
}
inline int newNode(int v){
	val[cnt] = v;
	l[cnt] = r[cnt] = 0;
	sz[cnt] = 1;
	tag[cnt] = false;
	pri[cnt] = ran();
	return cnt++;
}
inline int Sz(int x){
	return x ? sz[x] : 0;
}
inline void push(int x){
	tag[l[x]] ^= tag[x], tag[r[x]] ^= tag[x];
	if(tag[x]) swap(l[x], r[x]);
	tag[x] = false;
}
inline void pull(int x){
	sz[x] = Sz(l[x]) + Sz(r[x]) + 1;
}
void split(int o, int &a, int &b, int k){
	push(o);
	if(!o){
		a = b = 0;
		return;
	}
	if(Sz(l[o]) + 1 <= k){
		a = o;
		split(r[o], r[a], b, k - Sz(l[o]) - 1);
		pull(a);
	} else {
		b = o;
		split(l[o], a, l[b], k);
		pull(b);
	}
}
int merge(int a, int b){
	push(a), push(b);
	if(!a or !b) return a ? a : b;
	if(pri[a] < pri[b]){
		r[a] = merge(r[a], b);
		pull(a);
		return a;
	}
	l[b] = merge(a, l[b]);
	pull(b);
	return b;
}
void dfs(int u){
	push(u);
	if(l[u])dfs(l[u]);
	W(u);
	if(r[u])dfs(r[u]);
}
/* End Treap */

int main(){
	n = R(), m = R();
	int root = newNode(1);
	for(int i = 2; i <= n; ++i)
		root = merge(root, newNode(i));
	int a, b, c, d;
	for(; m; --m){
		if(Rc() == 'R'){
			a = R(), b = R();
			int eek, yas, jiz, owo;
			split(root, owo, jiz, b);
			split(owo, eek, yas, a - 1);
			tag[yas] = !tag[yas];
			root = merge(eek, merge(yas, jiz));
		} else {
			a = R(), b = R(), c = R(), d = R();
			int A, B, C, D, E, owo;
			split(root, owo, E, d);
			split(owo, root, D, c - 1);
			split(root, owo, C, b);
			split(owo, A, B, a - 1);
			root = merge(A, merge(merge(D, C), merge(B, E)));
		}
	}
	dfs(root);
	write(1,OB,OP);
	return 0;
}