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

const int N = 111, INF = INT_MAX;
struct DIN{
	struct E{
		int v, c, r;
		E(int v, int c, int r):
			v(v), c(c), r(r){}
	};
	vector<E> adj[N];
	void add(int u, int v, int c){
		adj[u].pb(v, c, (int) adj[v].size());
		adj[v].pb(u, 0, (int) adj[u].size() - 1);
	}
	int n, s, t;
	void init(int nn, int ss, int tt){
		n = nn, s = ss, t = tt;
		for(int i = 0; i <= n; ++i)
			adj[i].clear();
	}
	int le[N], it[N];
	int bfs(){
		fill(le, le + N, -1); le[s] = 0;
		queue<int> q; q.push(s);
		while(!q.empty()){
			int u = q.front(); q.pop();
			for(auto [v, c, r]: adj[u]){
				if(c > 0 and le[v] == -1)
					le[v] = le[u] + 1, q.push(v);
			}
		}
		return ~le[t];
	}
	int dfs(int u, int f){
		if(u == t) return f;
		for(int &i = it[u]; i < (int) adj[u].size(); ++i){
			auto &[v, c, r] = adj[u][i];
			if(c > 0 and le[v] == le[u] + 1){
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
	int flow(){
		int ans = 0, d;
		while(bfs()){
			fill(it, it + N, 0);
			while((d = dfs(s, INF)) > 0) ans += d;
		}
		return ans;
	}
} din;
struct EUL{
	struct E{
		int v; bool vis;
		E(int v): v(v), vis(false){}
	};
	vector<E> adj[N];
	void add(int u, int v){ adj[u].pb(v); }
	int n;
	void init(int nn){
		n = nn;
		for(int i = 0; i <= n; ++i)
			adj[i].clear();
	}
	vector<int> ans;
	void tour(int u){
		for(auto &[v, vis]: adj[u]){
			if(vis) continue;
			vis = true;
			tour(v);
			ans.pb(u);
		}
	}
	void print(){
		while(!ans.empty()){
			cout << ans.back() << ' ';
			ans.pop_back();
		}
		cout << 1 << '\n';
	}
} eul;

inline void gg(){ cout << "No euler circuit exist\n\n"; }
void solve(){
	int n, m; cin >> n >> m;
	din.init(n + 1, 0, n + 1);
	eul.init(n);

	vector<int> deg(n + 1, 0);

	for(; m; --m){
		int u, v; char d;
		cin >> u >> v >> d;
		++deg[u], --deg[v];
		if(d == 'U') din.add(u, v, 1);
		else eul.add(u, v);
	}

	int sum = 0;
	for(int i = 1; i <= n; ++i){
		if(deg[i] % 2 != 0) return gg();
		if(deg[i] > 0) din.add(0, i, deg[i] / 2), sum += deg[i] / 2;
		if(deg[i] < 0) din.add(i, n + 1, -deg[i] / 2);
	}

	if(din.flow() != sum) return gg();
	
	for(int u = 1; u <= n; ++u){
		for(auto [v, c, r]: din.adj[u])
			if(c > 0 and 1 <= v and v <= n)
				eul.add(u, v);
	}
	eul.tour(1);
	eul.print();
	cout << '\n';
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t; cin >> t;
	for(; t; --t) solve();
	return 0;
}
