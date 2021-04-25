#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'&&c!=-1);if(c==-1)return 0;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=' ';if(OP>65516)write(1,OB,OP),OP=0;}

const int N = 1e5 + 225;

/* Start Treap*/
int val[N], l[N], r[N], sz[N], cnt = 1;
unsigned pri[N];
inline unsigned ran(){
	static unsigned x = 131;
	return ++(x *= 0xdefaced);
}
inline int newNode(int v){
	val[cnt] = v;
	l[cnt] = r[cnt] = 0;
	sz[cnt] = 1;
	pri[cnt] = ran();
	return cnt++;
}
inline int Sz(int x){
	return x ? sz[x] : 0;
}
// inline void push(int x){
	// return;
// }
inline void pull(int x){
	sz[x] = Sz(l[x]) + Sz(r[x]) + 1;
}
void szsplit(int o, int &a, int &b, int k){
	// push(o);
	if(!o){
		a = b = 0;
		return;
	}
	if(Sz(l[o]) + 1 <= k){
		a = o;
		szsplit(r[o], r[a], b, k - Sz(l[o]) - 1);
		pull(a);
	} else {
		b = o;
		szsplit(l[o], a, l[b], k);
		pull(b);
	}
}
int merge(int a, int b){
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
inline void take(int &root, int p){
	int a, b, c, eek;
	szsplit(root, eek, c, p + 1);
	szsplit(eek, a, b, p);
	W(val[b]);
	root = merge(a, c);
}

/* End Treap */

int n, nxt[N];

int main(){
	while(n = R(), n != 0){
		for(int i = 0; i < n; ++i)
			nxt[i] = R();
		cnt = 1;
		int root = newNode(1);
		for(int i = 2; i <= n; ++i)
			root = merge(root, newNode(i));

		int p = 0, sum = n;
		for(int i = 0; i < n; ++i){
			p = (p + nxt[i] - 1) % sum;
			take(root, p);
			--sum;
		}
		OB[OP++] = '\n';
	}
	write(1,OB,OP);
	return 0;
}