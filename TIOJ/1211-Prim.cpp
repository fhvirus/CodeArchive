#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include<cstdio>
const int S = 1<<19;
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

#include<queue>
using namespace std;
const int N = 10001, M = 1e6, INF = 2147483647;
int n, m, ans;
int dist[N];
bool vis[N];

struct node{
	int v, c;
	bool operator<(const node &rhs) const{
		return c > rhs.c;
	}
};
vector<node> adj[N];
priority_queue<node> pq;

int main(){
	while(true){
		n = R(); m = R();
		if(n==0 and m==0) break;
		for(int i = 0; i <= n; ++i)
			dist[i] = INF, vis[i] = false, adj[i].clear();
		for(int u, v, c, i = 0; i < m; ++i){
			u = R(), v = R(), c = R();
			adj[u].push_back({v, c});
			adj[v].push_back({u, c});
		}
		if(m < n-1){ puts("-1"); continue;}

		dist[1] = 0; ans = 0;
		pq = {}; pq.push({1, 0});
		while(!pq.empty()){
			while(!pq.empty() and vis[pq.top().v]) pq.pop();
			if(pq.empty()) break;

			int u = pq.top().v; ans += pq.top().c; pq.pop();
			vis[u] = true, --n;
			if(n == 0) break;
			for(node v: adj[u]){
				if(!vis[v.v] and v.c < dist[v.v]){
					dist[v.v] = v.c;
					pq.push({v.v, v.c});
				}
			}
		}
		printf("%d\n", n == 0 ? ans : -1);
	}
	return 0;
}