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

const int kN = 100001;
const int kM = 2500052;
int n, m;
vector<int> adj[kN];
vector<pii> que[kN];
int f[kN], dep[kN], vis[kN], ans[kM];

int F(int a){ return a == f[a] ? a : f[a] = F(f[a]); }
void onion(int u, int v){
	u = F(u); v = F(v);
	if(u == v) return;
	f[v] = u;
}

void tarjan(int u, int p){
	vis[u] = 1;
	for(int v: adj[u]){
		if(v == p) continue;
		dep[v] = dep[u] + 1;
		tarjan(v, u);
		onion(u, v);
	}
	for(auto [v, i]: que[u]){
		if(!vis[v]) continue;
		ans[i] = dep[u] + dep[v] - 2 * dep[F(v)];
	}
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> m;
	for(int u, v, i = 1; i < n; ++i){
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	for(int u, v, i = 0; i < m; ++i){
		cin >> u >> v;
		que[u].pb(v, i);
		que[v].pb(u, i);
	}

	iota(f, f + n, 0);
	tarjan(0, 0);

	for(int i = 0; i < m; ++i)
		cout << ans[i] << '\n';
	return 0;
}
