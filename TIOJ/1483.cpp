#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

const int N = 1002, M = 1000000007;
int t, r, c;
/* BIT */
int bit[N][N];
inline void init(){
	for(int i = 1; i <= c; ++i)
		for(int j = 1; j < N; ++j)
			bit[i][j] = 0;
}
inline void madd(int &a, int v){
	a += v - M;
	a += (a>>31)&M;
}
inline void modify(int i, int y, int v){
	for(; i <= c; i += i & -i)
		for(int j = y; j <= N; j += j & -j)
			madd(bit[i][j], v);
}
inline int query(int i, int y){
	int ans = 0;
	for(; i > 0; i -= i & -i)
		for(int j = y; j > 0; j -= j & -j)
			madd(ans, bit[i][j]);
	return ans;
}
/* BIT */

inline void solve(){
	r = R(), c = R();
	init();
	for(int i = 1, v; i <= r; ++i)
		for(int j = 1; j <= c; ++j)
			v = R() + 1,
			modify(j, v, query(j, v - 1) + 1);
	W(query(c, N-1));
}

int main(){
	for(t = R(); t; --t) solve();
	write(1,OB,OP);
	return 0;
}