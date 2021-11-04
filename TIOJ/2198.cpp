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

struct DSU {
	int n; vector<int> f;
	DSU(int nn): n(nn), f(nn+1) { iota(AI(f), 0); }
	int F(int a){ return a == f[a] ? a : f[a] = F(f[a]); }
	bool M(int a, int b){
		a = F(a); b = F(b);
		if(a == b) return false;
		f[b] = a;
		return true;
	}
};

const int kN = 300003;
int N, M, A, B, Qupper;
vector<int> adj[kN];
vector<pair<int, ll>> flo[kN];
ll dp[kN];
int in[kN], ans;

void dfs(int u, int p){
	for(int v: adj[u]){
		if(v == p) continue;
		dfs(v, u);
		dp[u] += dp[v];
	}
	if(u == 1 or dp[u] == 0) return;
	++ans;
	if(dp[u] < 0) flo[p].pb(u, -dp[u]), ++in[u];
	else flo[u].pb(p, dp[u]), ++in[p];
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M >> A >> B >> Qupper;
	DSU dsu(N);
	for(int u, v, i = 0; i < M; ++i){
		cin >> u >> v;
		if(dsu.M(u, v)){
			adj[u].pb(v);
			adj[v].pb(u);
		}
	}

	for(int x, c, i = 0; i < A; ++i){
		cin >> x >> c;
		dp[x] = c;
	}
	for(int y, d, i = 0; i < B; ++i){
		cin >> y >> d;
		dp[y] = -d;
	}

	dfs(1, 1);

	queue<int> q;
	for(int i = 1; i <= N; ++i)
		if(in[i] == 0) q.push(i);

	cout << ans << '\n';
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(auto [v, c]: flo[u]){
			cout << u << ' ' << v << ' ' << c << '\n';
			--in[v];
			if(in[v] == 0)
				q.push(v);
		}
	}
	return 0;
}
