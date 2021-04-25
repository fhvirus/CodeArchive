#pragma Ofast
#pragma loop-opt(on)
#pragma GCC target("avx,avx2")
#include<unistd.h>
#define ll long long
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline ll R(){static char c;ll a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(ll n){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65510)write(1,OB,OP),OP=0;}

#define N 100001
int n, q;
ll a[N];

inline ll gcd(ll a, ll b){
	while(b != 0)
		a %= b, a ^= b, b ^= a, a ^= b;
	return a;
}
struct BIT{
	int n;
	ll val[N];
	inline void init(int _n, ll v[]){
		n = _n;
		for(int i = 1; i <= n; ++i)
			val[i] = v[i] - v[i - (i &  -i)];
	}
	inline ll query(int p){
		ll ans = 0;
		for(; p > 0; p -= p & -p) ans += val[p];
		return ans;
	}
	inline void modify(int p, int v){
		for(; p <= n; p += p & -p) val[p] += v;
	}
} bit;
struct segtree{
	int n;
	ll val[N * 2];
	inline void init(int _n, ll v[]){
		n = _n;
		for(int i = 0; i < n; ++i)
			val[i + n] = v[i];
		for(int i = n - 1; i > 0; --i)
			val[i] = gcd(val[i<<1], val[i<<1|1]);
	}
	inline ll query(int l, int r){
		ll ans = 0;
		for(l += n, r += n; l < r; l >>= 1, r >>= 1){
			if(l&1) ans = gcd(ans, val[l++]);
			if(r&1) ans = gcd(ans, val[--r]);
		}
		return ans < 0 ? -ans : ans;
	}
	inline void modify(int p, int v){
		val[p += n] += v;
		for(; p > 0; p >>= 1)
			val[p>>1] = gcd(val[p], val[p ^ 1]);
	}
} sgt;

int main(){
	n = R(), q = R();
	for(int i = 1; i <= n; ++i)
		a[i] = R();
	bit.init(n, a);
	for(int i = 0; i < n; ++i)
		a[i] = a[i + 1] - a[i];
	sgt.init(n, a);

	for(int cmd, l, r, k; q; --q){
		cmd = R(), l = R(), r = R();
		if(cmd == 1){
			k = R();
			bit.modify(l, k);
			bit.modify(r+1, -k);
			sgt.modify(l-1, k);
			sgt.modify(r, -k);
		} else {
			W(gcd(bit.query(r), sgt.query(l, r)));
		}
	}
	write(1,OB,OP);
	return 0;
}