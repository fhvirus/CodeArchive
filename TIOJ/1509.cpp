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
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

#include<vector>
#include<queue>
using namespace std;

const int N = 1e6+10, INF = 2147483647;
int m, n;
long long ans;
int dist[N];
bool vis[N];

struct edge{
	int v, c;
	edge(){}
	edge(int v, int c): v(v), c(c){}
};
struct cmp{
	bool operator()(edge a, edge b){
		return a.c > b.c;
	}
};

int head[N], prv[N];
edge to[N];
int rhead[N], rprv[N];
edge rto[N];
priority_queue<edge, vector<edge>, cmp> pq;

int main(){
	n = R(), m = R(), ans = 0;
	for(int i = 0; i <= n; ++i) head[i] = rhead[i] = -1;
	for(int p, q, r, i = 0; i < m; ++i){
		p = R(), q = R(), r = R();
		to[i] = {q, r}; prv[i] = head[p]; head[p] = i;
		rto[i] = {p, r}; rprv[i] = rhead[q]; rhead[q] = i;
	}

	for(int i = 1; i <= n; ++i) dist[i] = INF, vis[i] = false;
	dist[1] = 0;
	pq.push({1, 0});
	edge e, g;
	while(!pq.empty()){
		e = pq.top(); pq.pop();
		if(vis[e.v]) continue;
		vis[e.v] = true;
		for(int u = head[e.v]; u != -1; u = prv[u]){
			g.v = to[u].v;
			g.c = e.c + to[u].c;
			if(g.c < dist[g.v]){
				dist[g.v] = g.c;
				pq.push(g);
			}
		}
	}

	for(int i = 1; i <= n; ++i){
		if(dist[i] == INF){
			puts("0");
			return 0;
		}
		ans += dist[i];
		dist[i] = INF;
		vis[i] = false;
	}

	dist[1] = 0;
	pq.push({1, 0});
	while(!pq.empty()){
		e = pq.top(); pq.pop();
		if(vis[e.v]) continue;
		vis[e.v] = true;
		for(int u = rhead[e.v]; u != -1; u = rprv[u]){
			g.v = rto[u].v;
			g.c = e.c + rto[u].c;
			if(g.c < dist[g.v]){
				dist[g.v] = g.c;
				pq.push(g);
			}
		}
	}

	for(int i = 1; i <= n; ++i){
		if(dist[i] == INF){
			puts("0");
			return 0;
		}
		ans += dist[i];
		dist[i] = INF;
		vis[i] = false;
	}

	printf("%lld\n", ans);
}