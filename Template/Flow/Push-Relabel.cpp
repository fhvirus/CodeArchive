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

/*--------------------*/
// Problem: https://www.spoj.com/problems/FASTFLOW/
// Time: 4.90s
// Problem: https://vn.spoj.com/problems/FFLOW/
// Time: TLE
// Note:
// This is push-relabel algorithm.
/*--------------------*/

const int kN = 5005;
struct PPR {
	struct E {
		int v, c, r;
		E(int v, int c, int r): v(v), c(c), r(r) {}
	};
	vector<E> adj[kN];
	void add(int u, int v, int c){
		adj[u].pb(v, c, (int) adj[v].size());
		adj[v].pb(u, c, (int) adj[u].size() - 1);
	}
	int n, s, t;
	void init(int nn, int ss, int tt){
		n = nn; s = ss; t = tt;
		for(int i = 0; i <= n; ++i)
			adj[i].clear();
	}
	int hei[kN]; ll exc[kN];
	queue<int> exp;
	void preflow(){
		for(auto &[v, c, r]: adj[s]){
			if(c > 0 and v != s){
				exc[v] += c;
				adj[v][r].c += c;
				c = 0;
				if(v != t) exp.push(v);
			}
		}
	}
	void push(int u, int &v, int &c, int &r){
		ll f = min(exc[u], (ll) c);
		exc[u] -= f; exc[v] += f;
		c -= f; adj[v][r].c += f;
	}
	void relabel(int u){
		for(auto [v, c, r]: adj[u])
			if(c > 0) hei[u] = min(hei[u], hei[v]);
		++hei[u];
	}
	ll flow(){
		fill(hei, hei+n+1, 0); hei[s] = n;
		fill(exc, exc+n+1, 0);
		while(!exp.empty()) exp.pop();

		preflow();
		while(!exp.empty()){
			int u = exp.front(); exp.pop();
			relabel(u);
			for(auto &[v, c, r]: adj[u]){
				if(hei[u] == hei[v]+1 and c > 0){
					if(exc[v] == 0 and v != s and v != t) exp.push(v);
					push(u, v, c, r);
					if(exc[u] == 0) break;
				}
			}
			if(exc[u]) exp.push(u);
		}
		return exc[t];
	}
} ppr;

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int N, M; cin >> N >> M;
	ppr.init(N, 1, N);
	for(int u, v, c, i = 0; i < M; ++i){
		cin >> u >> v >> c;
		ppr.add(u, v, c);
	}
	cout << ppr.flow() << '\n';
	return 0;
}
