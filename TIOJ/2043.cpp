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

ll mpow(ll x, int e){
	ll r = 1;
	while(e) (e&1)&&(r=r*x%M), x=x*x%M, e>>=1;
	return r;
}

struct Comb{
	int n;
	vector<ll> fra, inv;
	Comb(){}
	Comb(int _n){
		n = _n;
		fra.resize(n + 1);
		inv.resize(n + 1);

		fra[0] = 1;
		for(int i = 1; i <= n; ++i) fra[i] = fra[i-1] * i % M;
		inv[n] = mpow(fra[n], M - 2);
		for(int i = n-1; i >= 0; --i) inv[i] = inv[i+1] * (i + 1) % M;
	}
	int operator()(int i, int j){
		return fra[i] * (inv[j] * inv[i - j] % M) % M;
	}
} C;

int n, ans;
vector<vector<int>> adj;

pii dfs(int u, int p){
	int sum = 1, s = 0;
	for(int v: adj[u]) if(v != p){
		auto [cs, ca] = dfs(v, u);
		sum = 1ll * C(s + cs, cs) * sum % M;
		sum = 1ll * ca * sum % M;
		s += cs;
	}
	s += 1;
	return pii(s, sum);
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n;
	C = Comb(n);
	adj.assign(n + 1, vector<int>());
	for(int i = 1, u, v; i < n; ++i){
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	for(int i = 1; i <= n; ++i){
		int tmp = dfs(i, 0).ss;
		ans += tmp;
		if(ans >= M) ans %= M;
		debug(tmp);
	}
	cout << ans;
	return 0;
}
