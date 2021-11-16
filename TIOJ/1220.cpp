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
int n, m;

int cc, f[kN], s[kN];
set<int> hs;
void init(){
	cc = n;
	for(int i = 1; i <= n; ++i) f[i] = i;
	for(int i = 1; i <= n; ++i) s[i] = 1;
	for(int i = 1; i <= n; ++i) hs.insert(i);
}
int Find(int u){ return u == f[u] ? u : f[u] = Find(f[u]); }
void Union(int u, int v){
	u = Find(u); v = Find(v);
	if(u == v) return;
	f[v] = u;
	s[u] += s[v];
	hs.erase(v);
	--cc;
}

vector<int> adj[kN];
int cnt[kN];

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> m;
	for(int u, v, i = 0; i < m; ++i){
		cin >> u >> v;
		if(u < v) swap(u, v);
		adj[u].pb(v);
	}

	init();

	for(int i = 1; i <= n and cc > 1; ++i){
		for(int v: adj[i]) ++cnt[Find(v)];
		vector<int> eek;
		for(int v: hs){
			if(v >= i) break;
			if(cnt[v] < s[v]) eek.pb(v);
		}
		for(int v: adj[i]) --cnt[Find(v)];
		for(int v: eek) Union(i, v);
	}
	cout << cc << '\n';
	return 0;
}
