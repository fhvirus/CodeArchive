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

const int N = 2002, M = 1e9 + 7;

ll mpow(ll x, int e){ ll r = 1; while(e) (e&1)&&(r=r*x%M), x=x*x%M, e>>=1; return r; }
ll money(ll x){ return mpow(x, M - 2);}

int n, ans;
vector<vector<int>> adj;
vector<ll> dp, sz, fr, in;

ll C(int i, int j){ return fr[i] * (in[j] * in[i - j] % M) % M; }
void add(int u, int v){
	sz[u] += sz[v];
	dp[u] = dp[u] * (C(sz[u] - 1, sz[v]) * dp[v] % M) % M;
}
void sub(int u, int v){
	dp[u] = dp[u] * money(C(sz[u] - 1, sz[v]) * dp[v] % M) % M;
	sz[u] -= sz[v];
}

void dfs(int u, int p){
	for(int v: adj[u]) if(v != p){
		dfs(v, u);
		add(u, v);
	}
	return;
}

void reroot(int u, int p){
	ans += dp[u]; if(ans >= M) ans -= M;
	for(int v: adj[u]) if(v != p){
		sub(u, v); add(v, u);
		reroot(v, u);
		sub(v, u); add(u, v);
	}
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n;

	adj.assign(n + 1, vector<int>());
	dp.assign(n + 1, 1);
	sz.assign(n + 1, 1);
	fr.resize(n + 1);
	in.resize(n + 1);

	fr[0] = 1;
	for(int i = 1; i <= n; ++i) fr[i] = fr[i-1] * i % M;
	in[n] = money(fr[n]);
	for(int i = n-1; i >= 0; --i) in[i] = in[i+1] * (i + 1) % M;

	for(int i = 1, u, v; i < n; ++i){
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}

	dfs(1, 0);
	reroot(1, 0);

	cout << ans;

	return 0;
}
