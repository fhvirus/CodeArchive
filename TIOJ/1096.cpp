#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c<'0') c = readchar();
	while(c>='0') ans=ans*10+(c^'0'), c=readchar();
	return ans;
}

const int N = 100, INF = 1e9;
int n, a, w[N][N], ans;

int main(){
	while((n = R()) != 0){
		FOR(i, n) FOR(j, n) a = R(), w[i][j] = (a == 0 ? INF : a);
		FOR(k, n) FOR(i, n) FOR(j, n)
			w[i][j] = (w[i][k] + w[k][j] < w[i][j]) ? (w[i][k] + w[k][j]) : w[i][j];
		ans = INF;
		FOR(i, n) ans = ans < w[i][i] ? ans : w[i][i];
		if(ans == INF) puts("-1");
		else printf("%d\n", ans);
	}
}