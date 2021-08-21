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

const int kN = 5005;
const int INF = 1e9 + 7;

struct EEK {
	int u, d, p;
	EEK(int u, int d, int p): u(u), d(d), p(p) {}
	bool operator < (const EEK &oth) const {
		return d > oth.d;
	}
};

int n, m;
vector<pii> adj[kN];

int to1[kN];
int best[kN], source[kN], second[kN];

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; ++i){
		to1[i] = INF;
		best[i] = INF;
		source[i] = -1;
		second[i] = INF;
	}

	for(int a, b, c, d, i = 0; i < m; ++i){
		cin >> a >> b >> c >> d;
		adj[a].pb(b, c);
		adj[b].pb(a, d);
		if(b == 1) to1[a] = c;
		if(a == 1) to1[b] = d;
	}

	best[1] = second[1] = -INF;
	priority_queue<EEK> pq;
	for(auto [v, w]: adj[1])
		pq.emplace(v, w, v);

	while(!pq.empty()){
		auto [u, d, p] = pq.top(); pq.pop();
		if(d > second[u]) continue;
		for(auto [v, w]: adj[u]){
			if(v == p) continue;
			if(d + w < best[v]){
				if(source[v] != p)
					second[v] = best[v];
				best[v] = d + w;
				source[v] = p;
				pq.emplace(v, best[v], p);
			} else if(p != source[v] and d + w < second[v]){
				second[v] = d + w;
				pq.emplace(v, second[v], p);
			}
		}
	}

	int ans = INF;
	for(int i = 2; i <= n; ++i)
		ans = min(ans, to1[i] + best[i]);
	cout << ans;
	return 0;
}
