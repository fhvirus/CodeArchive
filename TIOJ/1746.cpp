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
int N, K;
vector<int> adj[kN];

int dia, x, y, z;
int par[kN], no[kN][2];
pii dfs(int u){
	array<pii, 2> dp; dp[0] = pii(0, u);
	for(int v: adj[u]){
		if(v == par[u]) continue;
		par[v] = u; pii d = dfs(v);
		d.ff += (v == no[u][0] or v == no[u][1] ? -1 : 1);
		if(d > dp[0]) swap(d, dp[0]);
		if(d > dp[1]) dp[1] = d;
	}
	if(chmax(dia, dp[0].ff + dp[1].ff)) x = dp[0].ss, y = dp[1].ss, z = u;
	return dp[0];
}
int find_diameter(){
	dia = 0; dfs(1);
	return dia;
}
void remove(){
	while(x != z) no[par[x]][0] = x, x = par[x];
	while(y != z) no[par[y]][1] = y, y = par[y];
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> K;
	for(int u, v, i = 1; i < N; ++i){
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}

	int ans = 2 * (N-1);
	ans -= find_diameter() - 1;

	if(K == 2){
		remove();
		ans -= find_diameter() - 1;
	}

	cout << ans << '\n';

	return 0;
}
