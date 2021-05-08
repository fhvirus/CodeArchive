// Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef int64_t ll; typedef pair<int,int> pii; typedef pair<ll,ll> pll;
#define ff first
#define ss second
#define pb emplace_back
#define FOR(i,n) for(int i=0;i<(n);++i)
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)
#define OOF(i,a,b) for(int i=(a);i>=int(b);--i)
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}
template<class I>bool chmin(I&a,I b){return b<a?(a=b,true):false;} 
inline ll cdiv(ll x,ll m){return x/m+(x%m?(x<0)^(m>0):0);}
#ifdef OWO
#define safe cerr<<"\033[1;32m"<<__PRETTY_FUNCTION__<<" - "<<__LINE__<<" JIZZ\033[0m\n"
#define debug(args...) SDF(#args, args)
#define OIU(args...) ostream& operator<<(ostream&O,args)
#define LKJ(S,B,E,F) template<class...T>OIU(S<T...>s){O<<B;int c=0;for(auto i:s)O<<(c++?", ":"")<<F;return O<<E;}
LKJ(vector,'[',']',i)LKJ(deque,'[',']',i)LKJ(set,'{','}',i)LKJ(multiset,'{','}',i)LKJ(unordered_set,'{','}',i)LKJ(map,'{','}',i.ff<<':'<<i.ss)LKJ(unordered_map,'{','}',i.ff<<':'<<i.ss)
template<class T,size_t N>OIU(array<T,N>a){return O<<vector<T>(AI(a));}template<class...T>OIU(pair<T...>p){return O<<'('<<p.ff<<','<<p.ss<<')';}template<class...T>OIU(tuple<T...>t){return O<<'(',apply([&O](T...s){int c=0;(...,(O<<(c++?", ":"")<<s));},t),O<<')';}
template<class...T>void SDF(const char* s,T...a){int c=sizeof...(T);if(!c){cerr<<"\033[1;32mvoid\033[0m\n";return;}(cerr<<"\033[1;32m("<<s<<") = (",...,(cerr<<a<<(--c?", ":")\033[0m\n")));}
#else
#pragma GCC optimize("Ofast")
#define safe ((void)0)
#define debug(...) ((void)0)
#endif
const ll inf = 1e9, INF = 4e18;

struct DSU{
	int n, sz;
	vector<int> f;
	DSU(int _n): n(_n), sz(_n){
		f.assign(n + 1, 0);
		iota(AI(f), 0);
	}
	int F(int a){ return a == f[a] ? a : f[a] = F(f[a]);}
	bool M(int a, int b){
		a = F(a), b = F(b);
		if(a == b) return false;
		--sz;
		f[b] = a;
		return true;
	}
};

int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n, m, p; cin >> n >> m >> p;

	vector<bool> bad(n + 1, false);
	vector<vector<pii>> bto(n + 1, vector<pii>());
	for(int i = 0, u; i < p; ++i){
		cin >> u;
		bad[u] = true;
	}

	// beware of this case!
	if(n == 2 and p == 2){
		if(m == 0) cout << "impossible";
		else{
			int u, v, c; cin >> u >> v >> c;
			cout << c;
		}
		return 0;
	}

	vector<tuple<int, int, int>> line; // c, u, v
	for(int i = 0, u, v, c; i < m; ++i){
		cin >> u >> v >> c;
		if(bad[u] or bad[v]){
			if(bad[u]) bto[u].pb(c, v);
			if(bad[v]) bto[v].pb(c, u);
		} else line.pb(c, u, v);
	}

	sort(AI(line));

	DSU dsu(n);
	int ans = 0;
	for(auto [c, u, v]: line){
		debug(u, v, c);
		if(dsu.M(u, v)) ans += c;
	}

	for(int i = 1; i <= n; ++i){
		if(!bad[i]) continue;
		sort(AI(bto[i]));
		for(auto [c, v]: bto[i]){
			if(bad[v]) continue;
			ans += c;
			dsu.M(i, v);
			break;
		}
	}

	if(dsu.sz != 1) cout << "impossible";
	else cout << ans;
	return 0;
}
