#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}


#include<queue>
const int N = 1000+1, E = 2e6;
const int INF = 2147483647;
int n, m, st, ed;
int dist[N];
bool vis[N];
struct edge{
	int v; int c;
	edge(){}
	edge(int v, int c): v(v), c(c){}
};
std::vector<edge> adj[N];
struct cmp{
	bool operator()(edge a, edge b){
		return a.c > b.c;
	}
};

int main(){
	while(true){
		n = R(), m = R();
		if(n == 0) break;
		st = R(), ed = R();
		for(int i = 1; i <= n; ++i){
			vis[i] = false, dist[i] = INF;
			adj[i].clear();
		}
		for(int a, b, c, i = 0; m; --m){
			a = R(), b = R(), c = R();
			adj[a].push_back({b, c});
			adj[b].push_back({a, c});
		}

		std::priority_queue<edge, std::vector<edge>, cmp> pq;
		dist[st] = 0;
		pq.push({st, 0});
		edge e, g;
		while(!pq.empty()){
			e = pq.top(); pq.pop();
			if(vis[e.v]) continue;
			vis[e.v] = true;
			if(e.v == ed) break;
			for(edge u : adj[e.v]){
				g = {u.v, u.c + e.c};
				if(g.c < dist[g.v]){
					dist[g.v] = g.c;
					pq.push(g);
				}
			}
		}
		if(vis[ed]) printf("%d\n", dist[ed]);
		else puts("He is very hot");
	}
}