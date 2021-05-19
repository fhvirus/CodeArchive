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

struct CostFlow{
	static const int N = 210;
	static const int INF = 1e9;
	struct Edge{
		int to, cap, rev, cost;
		Edge(){}
		Edge(int t, int c, int r, int co):
			to(t), cap(c), rev(r), cost(co){}
	};
	vector<Edge> adj[N];
	void addEdge(int u, int v, int cap, int cost){
		adj[u].pb(v, cap, (int)adj[v].size(), cost);
		adj[v].pb(u, 0, (int)adj[u].size()-1,-cost);
	}
	int n, s, t;
	void init(int _n, int _s, int _t){
		n = _n, s = _s, t = _t;
		for(int i = 0; i <= n; ++i)
			adj[i].clear();
	}
	int par[N], pi[N], dis[N];
	bool inq[N];
	int q[N * N], he, ta;
	pair<int, int> flow(){
		int flow = 0, cost = 0;
		while(true){
			for(int i = 0; i < N; ++i) dis[i] = INF, inq[i] = false;
			dis[s] = 0;
			he = ta = 0; q[ta++] = s;
			while(he < ta){
				int u = q[he++];
				inq[u] = false;
				for(int i = 0, v; i < (int) adj[u].size(); ++i){
					Edge e = adj[u][i]; v = e.to;
					if(e.cap > 0 and chmin(dis[v], dis[u] + e.cost)){
						par[v] = u;
						pi[v] = i;
						if(!inq[v]){
							inq[v] = true;
							q[ta++] = v;
						}
					}
				}
			}
			if(dis[t] == INF) break;

			int mnf = INF;
			for(int i = t; i != s; i = par[i])
				chmin(mnf, adj[par[i]][pi[i]].cap);
			flow += mnf, cost += mnf * dis[t];
			for(int i = t; i != s; i = par[i]){
				adj[par[i]][pi[i]].cap -= mnf;
				adj[i][adj[par[i]][pi[i]].rev].cap += mnf;
			}
		}
		return {flow, cost};
	}
} flow;

void solve(int n){
	flow.init(n * 2 + 2 + 1, 0, n + n + 1);
	for(int i = 1; i <= n; ++i){
		flow.addEdge(0, i, 1, 0);
		flow.addEdge(n + i, n + n + 1, 1, 0);
		for(int j = 1; j <= n; ++j){
			int v; cin >> v;
			if(v < 0) v = 0;
			flow.addEdge(i, n + j, 1, 100 - v);
		}
	}
	cout << 100 * n - flow.flow().ss << '\n';
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n; while(cin >> n && n) solve(n);
	return 0;
}
