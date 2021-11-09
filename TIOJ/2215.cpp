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
const int kL = 17;
int n, dep[kN], anc[kL][kN];

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n;
	auto p = anc[0]; p[1] = 1;
	for(int i = 2; i <= n; ++i) cin >> p[i];
	for(int i = 2; i <= n; ++i) dep[i] = dep[p[i]] + 1;
	for(int l = 1; l < kL; ++l)
		for(int i = 1; i <= n; ++i)
			anc[l][i] = anc[l-1][anc[l-1][i]];

	auto lca = [](int u, int v){
		if(dep[u] < dep[v]) swap(u, v);
		for(int d = dep[u] - dep[v], l = 0; (1<<l) <= d; ++l)
			if(d>>l & 1) u = anc[l][u];
		if(u == v) return u;
		for(int l = kL-1; l >= 0; --l)
			if(anc[l][u] != anc[l][v]){
				u = anc[l][u];
				v = anc[l][v];
			}
		return anc[0][u];
	};

	int ans = 0, u = 1, v = 1;
	for(int d, e, i = 2; i <= n; ++i){
		d = dep[u] + dep[i] - 2 * dep[lca(u, i)];
		e = dep[v] + dep[i] - 2 * dep[lca(v, i)];
		if(d < e){ swap(d, e); swap(u, v); }
		if(d > ans){ v = i; ans = d; }
		cout << ans << '\n';
	}
	return 0;
}

