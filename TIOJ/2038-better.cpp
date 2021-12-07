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

// What's better than the other:
// 1. After some observation, we can see that the DS is useless
//    because the current node must have the least degree
//    due to the rule we order them.
// 2. We don't have to find the vertex with smallest degree
//    in O(1) time in phase 1, do it in O(N) would be enough.
//    This caused a significant implementation difficulty drop.

struct DSU {
	int n; vector<int> f, s;
	DSU (int nn) : n(nn), f(nn+1, 0), s(nn+1, 1) { iota(AI(f), 0); }
	int F(int u) { return u == f[u] ? u : f[u] = F(f[u]); }
	void M(int u, int v){
		u = F(u); v = F(v);
		if(u == v) return;
		f[v] = u;
		s[u] += s[v];
	}
};

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

	int N, M; cin >> N >> M;
	vector<vector<int>> adj(N+1);
	vector<int> deg(N+1, 0);
	for(int u, v, i = 0; i < M; ++i){
		cin >> u >> v;
		adj[u].pb(v); ++deg[u];
		adj[v].pb(u); ++deg[v];
	}

	vector<int> ord(N); iota(AI(ord), 1);
	for(int k = 0; k < N; ++k) {
		int &u = ord[k];
		for(int i = k+1; i < N; ++i)
			if(deg[u] > deg[ord[i]]) swap(u, ord[i]);
		for(int v: adj[u]) --deg[v];
	}
	reverse(AI(ord));

	vector<bool> alive(N+1, 0);
	DSU dsu(N);
	int ans = 0;
	for(int k = 0; k < N; ++k){
		int &u = ord[k];
		int cur = 0;
		for(int v: adj[u])
			if(alive[v]){
				dsu.M(u, v);
				++cur;
			}
		ans = max(ans, cur * dsu.s[dsu.F(u)]);
		alive[u] = true;
	}

	cout << ans << '\n';

	return 0;
}
