// Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef int64_t ll; typedef pair<int,int> pii; typedef pair<ll,ll> pll;
#define ff first
#define ss second
#define pb emplace_back
#define FOR(i,n) for(int i=0;i<(n);++i)
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)
#define OOF(i,a,b) for(int i=(a);i>=int(b);--i)
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}
template<class I>bool chmin(I&a,I b){return b<a?(a=b,true):false;} 
inline ll cdiv(ll x,ll m){return x/m+(x%m?(x<0)^(m>0):0);}
#ifdef OWO
#define safe cerr<<"\033[1;32m"<<__PRETTY_FUNCTION__<<" - "<<__LINE__<<" JIZZ\033[0m\n"
#define debug(args...) SDF(#args, args)
#define OIU(args...) ostream& operator<<(ostream&O,args)
#define LKJ(S,B,E,F) template<class...T>OIU(S<T...>s){O<<B;int c=0;for(auto i:s)O<<(c++?", ":"")<<F;return O<<E;}
LKJ(vector,'[',']',i)LKJ(deque,'[',']',i)LKJ(set,'{','}',i)LKJ(multiset,'{','}',i)LKJ(unordered_set,'{','}',i)LKJ(map,'{','}',i.ff<<':'<<i.ss)LKJ(unordered_map,'{','}',i.ff<<':'<<i.ss)
template<class T,size_t N>OIU(array<T,N>a){return O<<vector<T>(AI(a));}template<class...T>OIU(pair<T...>p){return O<<'('<<p.ff<<','<<p.ss<<')';}template<class...T>OIU(tuple<T...>t){return O<<'(',apply([&O](T...s){int c=0;(...,(O<<(c++?", ":"")<<s));},t),O<<')';}
template<class...T>void SDF(const char* s,T...a){int c=sizeof...(T);if(!c){cerr<<"\033[1;32mvoid\033[0m\n";return;}(cerr<<"\033[1;32m("<<s<<") = (",...,(cerr<<a<<(--c?", ":")\033[0m\n")));}
#else
#pragma GCC optimize("Ofast")
#define safe ((void)0)
#define debug(...) ((void)0)
#endif
const int INF = 2147483647;

struct Dinic{
	static const int N = 225;
	struct Edge{
		int to, cap, rev;
		Edge(int t = 0, int c = 0, int r = 0):
			to(t), cap(c), rev(r){}
	};
	vector<Edge> G[N];
	void addEdge(int u, int v, int c){
		G[u].pb(v, c, (int) G[v].size());
		G[v].pb(u, 0, (int) G[u].size() - 1);
	}
	int n, s, t;
	void init(int _n, int _s, int _t){
		n = _n, s = _s, t = _t;
		for(int i = 0; i <= n; ++i)
			G[i].clear();
	}
	int level[N], iter[N];
	void bfs(){
		memset(level, -1, sizeof(level));
		level[s] = 0;
		queue<int> q; q.push(s);
		while(!q.empty()){
			int u = q.front(); q.pop();
			for(Edge e: G[u]){
				if(e.cap > 0 and level[e.to] == -1){
					level[e.to] = level[u] + 1;
					q.push(e.to);
				}
			}
		}
	}
	int dfs(int u, int flow){
		if(u == t) return flow;
		for(int &i = iter[u]; i < (int) G[u].size(); ++i){
			Edge &e = G[u][i];
			if(e.cap > 0 and level[e.to] == level[u] + 1){
				int ret = dfs(e.to, min(flow, e.cap));
				if(ret > 0){
					e.cap -= ret;
					G[e.to][e.rev].cap += ret;
					return ret;
				}
			}
		}
		return 0;
	}
	ll flow(){
		ll ret = 0;
		while(true){
			bfs();
			if(level[t] == -1) break;
			memset(iter, 0, sizeof(iter));
			int tmp;
			while((tmp = dfs(s, INF)) > 0)
				ret += tmp;
		}
		return ret;
	}
} dinic;

int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n; cin >> n;
	dinic.init(n * 2 + 2, 0, n * 2 + 1);
	FOO(i,1,n){
		int a; cin >> a;
		dinic.addEdge(i, i + n, a);
	}
	int m; cin >> m;
	vector<bool> in(n + 1, 0), ou(n + 1, 0);
	FOR(_,m){
		int u, v; cin >> u >> v;
		ou[u] = true; in[v] = true;
		dinic.addEdge(u + n, v, INF);
	}
	FOO(i,1,n){
		if(!in[i]) dinic.addEdge(0, i, INF);
		if(!ou[i]) dinic.addEdge(i + n, n * 2 + 1, INF);
	}
	cout << dinic.flow();
	return 0;
}
