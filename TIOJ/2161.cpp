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

const int kN = 200002;

int N, Q;
vector<pii> adj[kN];

int dep[kN], par[kN], cost[kN], f[kN];

void dfs(int u, int p){
	for(auto [v, w]: adj[u]){
		if(v == p) continue;
		dep[v] = dep[u] + 1;
		par[v] = u;
		cost[v] = w;
		dfs(v, u);
	}
}

int F(int u) { return u == f[u] ? u : f[u] = F(f[u]); }

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> Q;
	for(int u, v, w, i = 1; i < N; ++i){
		cin >> u >> v >> w;
		adj[u].pb(v, w);
		adj[v].pb(u, w);
	}

	dfs(1, 1);

	for(int i = 1; i <= N; ++i) f[i] = i;

	for(int a, b, i = 0; i < Q; ++i){
		cin >> a >> b;
		a = F(a); b = F(b);
		int ans = 0;
		while(a != b){
			if(dep[a] < dep[b]) swap(a, b);
			ans += cost[a];
			f[a] = F(par[a]);
			a = F(a);
		}
		cout << ans << '\n';
	}

	return 0;
}

