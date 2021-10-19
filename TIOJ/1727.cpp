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

const int kN = 2002;
const int inf = 1e9 + 7;
const ll INF = 1e18;

int N, K, F[kN], C[kN][kN];
pll p[kN];
int siz[kN];
vector<pii> adj[kN];

vector<pll> dfs(int u, int p){
	siz[u] = 1;
	vector<pll> dp(2);
	dp[0] = pll(0, -INF);
	dp[1] = pll(-INF, -F[u]);
	for(auto [v, w]: adj[u]){
		if(v == p) continue;
		auto sc = dfs(v, u);
		siz[u] += siz[v];
		dp.resize(siz[u] + 1, pll(-INF, -INF));
		for(int i = siz[u]; i >= 0; --i){
			for(int j = max(0, i - siz[v]); j <= i; ++j){
				ll d = max(sc[i-j].ff, sc[i-j].ss + w);
				dp[i].ss = max({ dp[i].ss, dp[j].ss + d, dp[j].ff + sc[i-j].ss });
				dp[i].ff = max({ dp[i].ff, dp[j].ff + d });
			}
		}
	}
	return dp;
}

void solve(){
	cin >> N >> K;
	K = min(K, N);
	for(int x, y, i = 0; i < N; ++i){
		cin >> x >> y >> F[i];
		p[i] = pll(x, y);
	}
	for(int i = 0; i < N; ++i)
		for(int j = 0; j < N; ++j)
			C[i][j] = (p[i].ff - p[j].ff) * (p[i].ff - p[j].ff)
				+ (p[i].ss - p[j].ss) * (p[i].ss - p[j].ss);

	for(int i = 0; i < N; ++i) adj[i].clear();

	// Prim
	ll tot = 0;
	{
		vector<int> vis(N, 0), dis(N, inf), prv(N, 0);		
		vis[0] = 1; dis[0] = 0;
		for(int v = 1; v < N; ++v)
			dis[v] = C[0][v];
		for(int k = 1; k < N; ++k){
			int mind = inf, mint = -1;
			for(int u = 1; u < N; ++u)
				if(!vis[u] and chmin(mind, dis[u]))
					mint = u;
			vis[mint] = 1; tot += mind;
			adj[mint].pb(prv[mint], mind);
			adj[prv[mint]].pb(mint, mind);
			for(int v = 1; v < N; ++v)
				if(!vis[v] and chmin(dis[v], C[mint][v]))
					prv[v] = mint;
		}
	}

	auto dp = dfs(0, 0);
	ll ans = INF;
	for(int i = 1; i <= K; ++i)
		ans = min(ans, tot - dp[i].ss);
	ans = min(ans, tot - dp[0].ff);
	cout << ans << '\n';
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T; cin >> T;
	for(; T; --T) solve();
	return 0;
}
