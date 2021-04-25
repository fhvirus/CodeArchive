#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void RS(char* s){
	int p = 1;
	while((s[0] = RC())<'0');
	while((s[p] = RC())>='0') ++p;
	s[p] = '\0';
}
#include<cstdio>
#include<algorithm>
using namespace std;

const int N = 10000, L = 14;
int t, n, q;
int head[N], to[N*2], prv[N*2];
int anc[L][N], depth[N];

void dfs(int u, int p){
	for(int v = head[u]; v != -1; v = prv[v])
		if(to[v] != p)
			anc[0][to[v]] = u,
			depth[to[v]] = depth[u] + 1,
			dfs(to[v], u);
}
inline void buildLCA(){
	depth[0] = 1, dfs(0, 0);
	for(int i = 1; i < L; ++i)
		for(int j = 0; j < n; ++j)
			anc[i][j] = anc[i-1][anc[i-1][j]];
}
inline int LCA(int u, int v){
	if(depth[u] < depth[v]) swap(u, v);
	int d = depth[u] - depth[v];
	for(int i = L - 1; i >= 0; --i)
		if((d>>i) & 1) u = anc[i][u];
	if(u == v) return u;

	for(int i = L - 1; i >= 0; --i)
		if(anc[i][u] != anc[i][v])
			u = anc[i][u],
			v = anc[i][v];
	return anc[0][u];
}
inline int walkup(int u, int k){
	for(int i = L - 1; i >= 0; --i)
		if((k>>i) & 1) u = anc[i][u];
	return u;
}
inline void solve(int u, int v){
	int lca = LCA(u, v);
	int dis = depth[u] + depth[v] - 2 * depth[lca];
	int d = dis / 2;
	if(dis&1){
		int a = (depth[u] - depth[lca] >= d) ? walkup(u, d) : walkup(v, d + 1);
		int b = (depth[u] - depth[lca] >= d + 1) ? walkup(u, d + 1) : walkup(v, d);
		if(a > b) swap(a, b);
		printf("%d %d\n", a, b);
	} else
		printf("%d\n", (depth[u] - depth[lca] < d) ? walkup(v, d) : walkup(u, d));
}

char a[1001], b[1001];
int main(){
	t = R();
	for(; t; --t){
		n = R(), q = R();
		for(int i = 0; i < n; ++i) head[i] = -1;
		for(int i = 1, u, v, j = 0; i < n; ++i){
			u = R(), v = R();
			to[j] = v, prv[j] = head[u], head[u] = j++;
			to[j] = u, prv[j] = head[v], head[v] = j++;
		}
		buildLCA();
		for(; q; --q){
			int u, v;
			RS(a), u = R(), RS(b), v = R();
			printf("%s and %s: ", a, b);
			solve(u, v);
		}
	}
	return 0;
}