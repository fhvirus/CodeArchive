#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=1;i<=n;++i)
const int S = 1<<15;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

const int N = 1e5 + 1;
int n, head[N], to[N<<1], cost[N<<1], prv[N<<1];
int d1[N], d2[N], ans;

inline void dfs(int u, int p){
	int d = u;
	for(int v = head[u]; v != -1; v = prv[v])
		if(to[v] != p){
			dfs(to[v], u);
			if(d1[to[v]] + cost[v] > d1[u])
				d2[u] = d1[u], d1[u] = d1[to[v]] + cost[v];
			else if(d1[to[v]] + cost[v] > d2[u])
				d2[u] = d1[to[v]] + cost[v];
		}
	ans = ans > d1[u] + d2[u] ? ans : d1[u] + d2[u];
	return;
}

int main(){
	while((n = R()) != 0){
		FOR(i, n) head[i] = -1, d1[i] = d2[i] = 0;
		for(int i = 1, a, b, c, m = 0; i < n; ++i)
			a = R(), b = R(), c = R(),
			to[m] = b, cost[m] = c, prv[m] = head[a], head[a] = m++,
			to[m] = a, cost[m] = c, prv[m] = head[b], head[b] = m++;
		ans = 0, dfs(1, 0), printf("%d\n", ans);
	}
}