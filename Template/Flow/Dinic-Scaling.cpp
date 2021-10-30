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

/*--------------------*/
// Problem: https://www.spoj.com/problems/FASTFLOW/
// Time: 0.49s (slower than original Dinic on this problem)
// Problem: https://vn.spoj.com/problems/FFLOW/
// Time: 0.11s (faster)
// Note:
// This is Dinic's algorithm with scaling for undirected graph.
// Modify the add() function for directed ones.
/*--------------------*/

const int kN = 5005;
const int kL = 30;
const int INF = 1e9 + 7;
struct DIN {
	struct E {
		int v, c, r;
		E(int v, int c, int r): v(v), c(c), r(r) {}
	};
	vector<E> adj[kN];
	void add(int u, int v, int c){
		adj[u].pb(v, c, (int) adj[v].size());
		adj[v].pb(u, c, (int) adj[u].size() - 1);
	}
	int n, s, t, lim;
	void init(int nn, int ss, int tt){
		n = nn; s = ss; t = tt; lim = 1<<kL;
		for(int i = 0; i <= n; ++i)
			adj[i].clear();
	}
	int le[kN], it[kN];
	int bfs(){
		fill(le, le+n+1, -1); le[s] = 0;
		queue<int> q; q.push(s);
		while(!q.empty()){
			int u = q.front(); q.pop();
			for(auto [v, c, r]: adj[u]){
				if(le[v] == -1 and c >= lim){
					le[v] = le[u] + 1;
					q.push(v);
				}
			}
		}
		return ~le[t];
	}
	int dfs(int u, int f){
		if(u == t) return f;
		for(int &i = it[u]; i < (int) adj[u].size(); ++i){
			auto &[v, c, r] = adj[u][i];
			if(le[v] == le[u] + 1 and c > 0){
				int d = dfs(v, min(c, f));
				if(d > 0){
					c -= d;
					adj[v][r].c += d;
					return d;
				}
			}
		}
		return 0;
	}
	ll flow(){
		ll ans = 0, u;
		for(; lim > 0; lim >>= 1){
			while(bfs()){
				fill(it, it+n+1, 0);
				while(u = dfs(s, INF)) ans += u;
			}
		}
		return ans;
	}
} din;

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int N, M; cin >> N >> M;
	din.init(N, 1, N);
	for(int u, v, c, i = 0; i < M; ++i){
		cin >> u >> v >> c;
		din.add(u, v, c);
	}
	cout << din.flow() << '\n';
	return 0;
}
