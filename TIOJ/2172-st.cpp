// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[141592]; int OP;
inline char RC(){static char buf[141592],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,141592))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>141592)write(1,OB,OP),OP=0;}

#include<algorithm>
using namespace std;
const int N = 100001, L = 17;

int n, m;
int he[N], to[N * 2], pr[N * 2];
int dep[N], vis[N], tot;
int st[L + 1][N * 2];
void dfs(int u, int p = -1){
	vis[u] = tot++;
	st[0][vis[u]] = dep[u];
	for(int e = he[u], v; e != -1; e = pr[e]){
		if((v = to[e]) == p) continue;
		dep[v] = dep[u] + 1;
		dfs(v, u);
		st[0][tot++] = dep[u];
	}
}
void buildst(){
	int lg = __lg(tot);
	for(int l = 1; l <= lg; ++l)
		for(int i = 0; i + (1<<l) < tot; ++i)
			st[l][i] = min(st[l-1][i], st[l-1][i + (1<<l-1)]);
}

int main(){
	n = R(), m = R();
	for(int i = 0; i < n; ++i) he[i] = -1;
	for(int u, v, i = 1, j = 0; i < n; ++i){
		u = R(), v = R();
		to[j] = v; pr[j] = he[u]; he[u] = j++;
		to[j] = u; pr[j] = he[v]; he[v] = j++;
	}
	dfs(0);
	buildst();
	for(int u, v, d, l; m; --m){
		u = R(), v = R();
		d = dep[u] + dep[v];
		u = vis[u], v = vis[v];
		if(u > v) swap(u, v);
		l = __lg(v - u);
		W(d - 2 * min(st[l][u], st[l][v - (1<<l) + 1]));
	}
	write(1,OB,OP);
	return 0;
}
