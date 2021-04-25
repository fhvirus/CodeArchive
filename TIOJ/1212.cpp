#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=1;i<=n;++i)
const int S = 1<<18;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

#include<cstring>
#include<vector>
using namespace std;
#define INF 2147483647
int n, m, ans, a, b;
vector<short> adj[501];
inline int min(int a, int b){
	return a < b ? a : b;
}
bool indeg[501];
int vis[501], inq[501], t;
int dis[501];
int Q[500], front, back;
inline int bfs(int a){
	++t;
	memset(dis, 0, 501 * 4);
	front = 0, back = 1, Q[0] = a, vis[a] = inq[a] = t, dis[a] = 0;
	while(front < back){
		int u = Q[front++];
		vis[u] = t;
		for(int v: adj[u])
			if(v == a)
				return dis[u] + 1;
			else if(inq[v] != t)
				Q[back++] = v, dis[v] = dis[u] + 1, inq[v] = t;
	}
	return INF;
}

int main(){
	while((n = R()) != 0){
		m = R(), ans = INF;
		FOR(i, n) adj[i].clear(), indeg[i] = false;
		FOR(i, m) a = R(), b = R(), adj[a].push_back(b), indeg[b] = true;
		FOR(i, n) if(indeg[i]) ans = min(ans, bfs(i));
		printf("%d\n", ans == INF ? 0 : ans);
	}
}