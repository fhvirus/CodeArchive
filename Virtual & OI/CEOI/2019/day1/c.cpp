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

typedef tuple<int, int, ll> triple;

const int kN = 100001;
int n, q; ll w;
pii edg[kN]; ll wei[kN];
vector<pll> adj[kN];
int par[kN];
ll dep[kN], dp[kN];
multiset<ll> s;


void init(){
	for(int w = 0; w < n-1; ++w) s.insert(wei[w]);
}
void rm(ll v){
	auto it = s.find(v);
	s.erase(it);
}
ll upd(ll d, ll e){
	rm(wei[d]);
	wei[d] = e;
	s.insert(e);
	if(s.size() == 1) return *begin(s);
	return *prev(end(s)) + *prev(prev(end(s)));
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> q >> w;
	for(int i = 0; i < n-1; ++i){
		int u, v; ll c; cin >> u >> v >> c;
		edg[i] = pii(u, v);
		wei[i] = c;
		adj[u].pb(v, i);
		adj[v].pb(u, i);
	}
	init();
	ll last = 0;
	for(int i = 0; i < q; ++i){
		ll d, e; cin >> d >> e;
		d = (d + last) % (n-1);
		e = (e + last) % w;
		cout << (last = upd(d, e)) << '\n';
	}
	return 0;
}
