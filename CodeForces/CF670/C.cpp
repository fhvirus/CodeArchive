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
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

#include<algorithm>
#include<vector>
using namespace std;

const int N = 1e5 + 1;
int t, n;
vector<int> adj[N];
int mx[N], sz[N], par[N];

void dfs(int u, int p){
	par[u] = p;
	sz[u] = 1, mx[u] = -1;
	for(int v: adj[u]){
		if(v == p) continue;
		dfs(v, u);
		sz[u] += sz[v];
		mx[u] = max(mx[u], sz[v]);
	}
	if(u != 1) mx[u] = max(mx[u], n - sz[u]);
}

int dfs2(int u, int p){
	if(sz[u] == 1) return u;
	for(int v: adj[u])
		if(v != p) return dfs2(v, u);
	return u;
}

int main(){
	t = R();
	for(; t; --t){
		n = R();
		for(int i = 0; i <= n; ++i)
			adj[i].clear();
		for(int i = 1, a, b; i < n; ++i)
			a = R(), b = R(),
			adj[a].push_back(b),
			adj[b].push_back(a);
		if(n % 2 == 1){ printf("1 2\n1 2\n"); continue;}
		dfs(1, 0);

		// printf("\nJizz: \n");
		// for(int i = 1; i <= n; ++i)
		// 	printf("%d %d\n", sz[i], mx[i]);
		// printf("\n");

		int c1 = 1, c2;
		for(int i = 1; i <= n; ++i)
			if(mx[i] < mx[c1]) c1 = i;
		for(int i = c1 + 1; i <= n; ++i)
			if(mx[i] == mx[c1]){ c2 = i; break;}

		// printf("%d %d\n", c1, c2);

		if(sz[c1] < sz[c2]) swap(c1, c2);
		int jizz = dfs2(c2, c1);
		printf("%d %d\n", par[jizz], jizz);
		printf("%d %d\n", c1, jizz);
	}
}