#pragma Ofast
#pragma loop-opt(on)
#pragma GCC target("avx,avx2")
#include<unistd.h>
char OB[20]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(long long n){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}
#define FOR(i,n) for(int i=1;i<=n;++i)
const int N = 1002;
int m, n, a[N][N];
long long ans;

int main(){
	m = R(), n = R();
	FOR(i,m)FOR(j,n) a[i][j] = R();
	FOR(i,m)FOR(j,n){
		ans += a[i][j];
		if(a[i+1][j] > a[i][j]) ans += a[i+1][j];
		if(a[i-1][j] > a[i][j]) ans += a[i-1][j];
		if(a[i][j+1] > a[i][j]) ans += a[i][j+1];
		if(a[i][j-1] > a[i][j]) ans += a[i][j-1];
	}
	W(ans);
}