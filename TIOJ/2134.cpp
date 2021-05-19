// Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<int,int> pii; typedef pair<ll,ll> pll;
#define ff first
#define ss second
#define pb emplace_back
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}
template<class I>bool chmin(I&a,I b){return b<a?(a=b,true):false;} 
#ifdef OWO
#define debug(args...) SDF(#args, args)
#define OIU(args...) ostream& operator<<(ostream&O,args)
#define LKJ(S,B,E,F) template<class...T>OIU(S<T...>s){O<<B;int c=0;for(auto i:s)O<<(c++?", ":"")<<F;return O<<E;}
LKJ(vector,'[',']',i)LKJ(deque,'[',']',i)LKJ(set,'{','}',i)LKJ(multiset,'{','}',i)LKJ(unordered_set,'{','}',i)LKJ(map,'{','}',i.ff<<':'<<i.ss)LKJ(unordered_map,'{','}',i.ff<<':'<<i.ss)
template<class...T>void SDF(const char* s,T...a){int c=sizeof...(T);if(!c){cerr<<"\033[1;32mvoid\033[0m\n";return;}(cerr<<"\033[1;32m("<<s<<") = (",...,(cerr<<a<<(--c?", ":")\033[0m\n")));}
template<class T,size_t N>OIU(array<T,N>a){return O<<vector<T>(AI(a));}template<class...T>OIU(pair<T...>p){return O<<'('<<p.ff<<','<<p.ss<<')';}template<class...T>OIU(tuple<T...>t){return O<<'(',apply([&O](T...s){int c=0;(...,(O<<(c++?", ":"")<<s));},t),O<<')';}
#else
#pragma GCC optimize("Ofast")
#define debug(...) ((void)0)
#endif

struct Dinic{
	static const int N = 1005;
	static const int INF = 1000000007;
	struct Edge{
		int to, cap, rev;
		Edge(){}
		Edge(int t, int c, int r):
			to(t), cap(c), rev(r){}
	};
	vector<Edge> adj[N];
	void addEdge(int u, int v, int c){
		adj[u].pb(v, c, (int)adj[v].size());
		adj[v].pb(u, 0, (int)adj[u].size() - 1);
	}
	int n, s, t;
	void init(int _n, int _s, int _t){
		n = _n, s = _s, t = _t;
		for(int i = 0; i <= n; ++i)
			adj[i].clear();
	}
	int lev[N], itr[N];
	void bfs(){
		fill(lev, lev + N, -1);
		lev[s] = 0;
		queue<int> q; q.push(s);
		while(!q.empty()){
			int u = q.front(); q.pop();
			for(Edge e: adj[u])
				if(e.cap > 0 and lev[e.to] == -1){
					lev[e.to] = lev[u] + 1;
					q.push(e.to);
				}
		}
	}
	int dfs(int u, int flow){
		if(u == t) return flow;
		for(int &i = itr[u]; i < (int) adj[u].size(); ++i){
			Edge &e = adj[u][i];
			if(e.cap > 0 and lev[e.to] == lev[u] + 1){
				int ret = dfs(e.to, min(flow, e.cap));
				if(ret > 0){
					e.cap -= ret;
					adj[e.to][e.rev].cap += ret;
					return ret;
				}
			}
		}
		return 0;
	}
	int flow(){
		int ret = 0;
		while(true){
			bfs();
			if(lev[t] == -1) break;
			fill(itr, itr + N, 0);
			int u;
			while((u = dfs(s, INF)) > 0)
				ret += u;
		}
		return ret;
	}
} dinic;

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n, m, k; cin >> n >> m >> k;
	dinic.init(n + m + 2, 0, n + m + 2);
	for(int i = 1; i <= n; ++i) dinic.addEdge(0, i, 1);
	for(int i = 1; i <= m; ++i) dinic.addEdge(n + i, n + m + 2, 1);
	dinic.addEdge(0, n + m + 1, k);
	for(int i = 1; i <= n; ++i) dinic.addEdge(n + m + 1, i, 1);
	for(int i = 1, t, x; i <= n; ++i){
		cin >> t;
		for(; t; --t){
			cin >> x;
			dinic.addEdge(i, n + x, 1);
		}
	}
	cout << dinic.flow();
	return 0;
}
