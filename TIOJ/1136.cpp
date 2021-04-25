//Knapsack DP is harder than FFT.
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}

#include<cstdio>
#define FOR(i,n) for(int i=0;i<(n);++i)

const int N = 100;
int n, t, deg[N];
double ans[N], tran[N][N];
double tmp[N], temp[N][N];
inline void multans(){
	FOR(i,n) {tmp[i] = ans[i]; ans[i] = 0;}
	FOR(i,n) FOR(k,n) ans[i] += tran[i][k] * tmp[k];
}
inline void multran(){
	FOR(i,n) FOR(j,n) {temp[i][j] = tran[i][j]; tran[i][j] = 0;}
	FOR(i,n) FOR(j,n) FOR(k,n) tran[i][j] += temp[i][k] * temp[k][j];
}

int main(){
	while(n = R(), t = R(), n != 0){
		FOR(i,n) FOR(j,n) tran[i][j] = 0;
		FOR(i,n) ans[i] = 1.0 / n;
		FOR(i,n) deg[i] = 0;

		int cnt = 0;
		for(int u, v, c = R(); c; --c){
			u = R() - 1, v = R() - 1;
			tran[u][v] = tran[v][u] = 1;
			++deg[u], ++deg[v];
		}

		FOR(i,n) FOR(j,n) if(deg[j] != 0) tran[i][j] /= deg[j];

		while(t){
			if(t & 1) multans();
			multran();
			t >>= 1;
		}
		printf("%.4lf\n", ans[R() - 1]);
	}
	return 0;
}
