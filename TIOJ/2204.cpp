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

const int kN = 505;
const int kC = 1e9;
const ll INF = 1e18;

const int MOD = 1e9+7;
void mad(int &u, int v){
	u = ((ll) u + v) % MOD;
}
int mul(int u, int v){
	return (ll) u * v % MOD;
}

typedef tuple<int, int, int> tri;
struct EEK {
	int u; ll d; int p;
	EEK(int u, ll d, int p): u(u), d(d), p(p) {}
	bool operator < (const EEK &oth) const {
		return d > oth.d;
	}
};

int n, m, q;
vector<tri> adj[kN];

ll dis[kN][kN];

typedef pair<ll, int> pli;
void solve(int u){
	vector<pli> best(n+1, pli(INF, -1));
	vector<pli> second(n+1, pli(INF, -1));
	vector<int> visBest(n+1, 0);
	vector<int> visSecond(n+1, 0);

	best[u] = pli(0ll, -1);

	for(int k = 0; k < 2 * n; ++k){
		pair<int, pli> mnBest(-1, pli(INF, -1));
		pair<int, pli> mnSecond(-1, pli(INF, -1));
		for(int i = 1; i <= n; ++i){
			if(!visBest[i] and chmin(mnBest.ss, best[i]))
				mnBest.ff = i;
			if(!visSecond[i] and chmin(mnSecond.ss, second[i]))
				mnSecond.ff = i;
		}

		if(min(mnBest.ss.ff, mnSecond.ss.ff) >= INF) break;

		int cur, p; ll d;
		if(mnBest.ss <= mnSecond.ss) cur = mnBest.ff, tie(d, p) = mnBest.ss, visBest[cur] = 1;
		else cur = mnSecond.ff, tie(d, p) = mnSecond.ss, visSecond[cur] = 1;

		for(auto [v, w, c]: adj[cur]){
			if(c == p) continue;
			if(d + w < best[v].ff){
				if(best[v].ss != c) second[v] = best[v];
				best[v] = pli(d + w, c);
			} else if(best[v].ss != c and d + w < second[v].ff){
				second[v] = pli(d + w, c);
			}
		}
	}

	for(int v = 1; v <= n; ++v) dis[u][v] = best[v].ff;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t; cin >> t;
	for(; t; --t){
		cin >> n >> m;
		for(int i = 1; i <= n; ++i)
			adj[i].clear();
		
		for(int u, v, w, c, i = 0; i < m; ++i){
			cin >> u >> v >> w >> c;
			adj[u].pb(v, w, c);
			adj[v].pb(u, w, c);
		}

		for(int i = 1; i <= n; ++i) solve(i);

		int ans = 0;
		for(int i = 1; i <= n; ++i){
			for(int j = i+1; j <= n; ++j){
				if(dis[i][j] == INF) continue;
				mad(ans, mul(dis[i][j] % MOD, i+j));
			}
		}
		cout << ans << '\n';
	}
	return 0;
}

