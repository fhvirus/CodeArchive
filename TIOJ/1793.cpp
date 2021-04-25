// Knapsack DP is harder than FFT.
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<queue>
using namespace std;
typedef pair<int,int> pii;
#define pb emplace_back
#define FOO(i,a,b) for(int i = (a); i <= (b); ++i)
template<typename I> bool chmin(I &a, I b){ return b < a ? (a = b, true) : false;}

const int N = 5005, M = 10005, INF = 1e9;
int n, m, a[N];
vector<pii> adj[N];
int main(){
	n = R(), m = R();
	for(int u, v, c, d; m; --m){
		u = R(), v = R(), c = R(), d = R();
		adj[u].pb(v, c);
		adj[v].pb(u, d);
	}

	FOO(i,2,n){
		a[i] = INF;
		for(auto [j, c]: adj[i]) if(j == 1) chmin(a[i], c);
	}

	auto dijkstra = [](int mask){
		vector<bool> vis(n + 1);
		vector<int> dis(n + 1, INF);
		priority_queue<pii, vector<pii>, greater<pii>> pq;

		dis[1] = 0; vis[1] = true;
		for(auto [v, c]: adj[1]){
			if(v & mask) chmin(dis[v], c), pq.emplace(c, v);
		}
		while(!pq.empty()){
			auto [d, u] = pq.top(); pq.pop();
			if(vis[u]) continue;
			vis[u] = true;
			for(auto [v, c]: adj[u])
				if(chmin(dis[v], c + d)) pq.emplace(dis[v], v);
		}
		return dis;
	};

	// auto artskjid = [](int mask){
	// 	vector<bool> vis(n + 1);
	// 	vector<int> dis(n + 1, INF);
	// 	priority_queue<pii, vector<pii>, greater<pii>> pq;

	// 	dis[1] = 0; vis[1] = true;
	// 	for(auto [v, c]: adj[1]){
	// 		if((v & mask) == 0) chmin(dis[v], c), pq.emplace(c, v);
	// 	}
	// 	while(!pq.empty()){
	// 		auto [d, u] = pq.top(); pq.pop();
	// 		if(vis[u]) continue;
	// 		vis[u] = true;
	// 		for(auto [v, c]: adj[u])
	// 			if(chmin(dis[v], c + d)) pq.emplace(dis[v], v);
	// 	}
	// 	return dis;
	// };

	int ans = INF;
	for(int mask = 1; mask <= n; mask <<= 1){
		auto dis = dijkstra(mask);
		// auto sid = artskjid(mask);
		FOO(i,2,n){
			if((i & mask) == 0 and a[i] != INF) chmin(ans, dis[i] + a[i]);
			// if((i & mask) != 0 and a[i] != INF) chmin(ans, sid[i] + a[i]);
		}
	}
	W(ans);
	return 0;
}