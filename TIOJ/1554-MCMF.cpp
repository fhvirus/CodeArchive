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

const double INF = 10, eps = 1e-7;

// MCMF from IOICamp 2021
struct CostFlow{
	static const int N = 50;
	struct Edge{
		int to, cap, rev;
		double cost;
		Edge(){}
		Edge(int t, int c, int r, double co):
			to(t), cap(c), rev(r), cost(co){}
	};
	vector<Edge> adj[N];
	void addEdge(int u, int v, int cap, double cost){
		adj[u].pb(v, cap, (int)adj[v].size(), cost);
		adj[v].pb(u, 0, (int)adj[u].size()-1, -cost);
	}
	int n, s, t;
	void init(int _n, int _s, int _t){
		n = _n, s = _s, t = _t;
		for(int i = 0; i <= n; ++i)
			adj[i].clear();
	}
	int par[N], pari[N];
	double dis[N];
	bool inq[N];
	pair<int, double> flow(){
		int flow = 0; double cost = 0;
		while(true){
			fill(dis, dis + N, INF);
			fill(inq, inq + N, false);
			dis[s] = 0;
			queue<int> q; q.push(s);
			while(!q.empty()){
				int u = q.front(); q.pop();
				inq[u] = false;
				for(int i = 0; i < (int)adj[u].size(); ++i){
					Edge e = adj[u][i];
					if(e.cap > 0 and dis[e.to] > dis[u] + e.cost + eps){
						dis[e.to] = dis[u] + e.cost;
						par[e.to] = u;
						pari[e.to] = i;
						if(!inq[e.to]){
							inq[e.to] = true;
							q.push(e.to);
						}
					}
				}
			}
			if(dis[t] + eps >= INF) break;
			int mnf = 1e9;
			for(int i = t; i != s; i = par[i])
				chmin(mnf, adj[par[i]][pari[i]].cap);
			flow += mnf, cost += mnf * dis[t];
			for(int i = t; i != s; i = par[i]){
				adj[par[i]][pari[i]].cap -= mnf;
				adj[i][adj[par[i]][pari[i]].rev].cap += mnf;
			}
		}
		return {flow, cost};
	}
} flow;

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n; cin >> n;
	flow.init(n * 2 + 2, 0, n + n + 1);
	for(int i = 1; i <= n; ++i){
		flow.addEdge(0, i, 1, 0);
		flow.addEdge(n + i, n + n + 1, 1, 0);
		for(int j = 1; j <= n; ++j){
			int v; cin >> v;
			double cost = -log10(v / 100.0 + eps);
			flow.addEdge(i, n + j, 1, cost);
		}
	}
	cout << setprecision(2) << fixed << pow(10, -flow.flow().ss) * 100;
	return 0;
}
