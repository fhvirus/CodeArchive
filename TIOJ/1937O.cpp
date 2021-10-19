#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2")
const int kBuf = 1<<16;
#include<unistd.h>
char OB[kBuf]; int OP;
inline char RC(){static char buf[kBuf],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,kBuf))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n,char e){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=e;if(OP>kBuf-12)write(1,OB,OP),OP=0;}

#define FOR(i,n) for(int i = 0; i < n; ++i)

const int kN = 2048;
int N;
char a[kN][kN], b[kN][kN];
int c[kN][kN];

signed main(){
	N = R();
	FOR(i,N) FOR(j,N) a[i][j] = R();
	FOR(i,N) FOR(j,N) b[i][j] = R();
	FOR(i,N) FOR(k,N) FOR(j,N) c[i][j] += a[i][k] * b[k][j];
	FOR(i,N) FOR(j,N) W(c[i][j], " \n"[j == N-1]);
	write(1,OB,OP);
	return 0;
}

