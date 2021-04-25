// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n, char e){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=e;if(OP>65516)write(1,OB,OP),OP=0;}

typedef long long ll;

ll mpow(ll x, ll e, ll m){
	ll r = 1;
	while(e){
		if(e&1) r = r * x % m;
		x = x * x % m;
		e >>= 1;
	}
	return r;
}

void solve(){
	ll M = R(), a = R(), b = R(), x1 = R(), y1 = R(), x2 = R(), y2 = R();

	ll m = (y2 - y1) * mpow(x2 - x1, M - 2, M) % M;
	m = (m + M) % M;

	ll x3 = m * m - x1 - x2;
	x3 %= M; if(x3 < 0) x3 += M;

	ll k = y1 - m * x1;
	k %= M; if(k < 0) k += M;

	W(x3, ' '); W((m * x3 + k) % M, '\n');
}

int main(){
	for(int t = R(); t; --t) solve();
	write(1,OB,OP);
	return 0;
}
