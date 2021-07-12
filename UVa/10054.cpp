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

const int kC = 51;

int n, cnt, deg[kC], adj[kC][kC];
vector<pii> ans;

void euler(int u){
	for(int v = 1; v < kC; ++v)
		if(adj[u][v]){
			--adj[u][v]; --adj[v][u]; ++cnt;
			euler(v);
			ans.pb(u, v);
		}
}

void solve(){
	cin >> n; cnt = 0;
	for(int i = 1; i < kC; ++i){
		deg[i] = 0;
		for(int j = 1; j < kC; ++j)
			adj[i][j] = 0;
	}
	for(int u, v, i = 0; i < n; ++i){
		cin >> u >> v;
		++adj[u][v]; ++adj[v][u];
		++deg[u]; ++deg[v];
	}

	int s = 0;
	for(int i = 1; i < kC; ++i)
		if(deg[i] % 2 != 0){
			cout << "some beads may be lost\n";
			return;
		} else if(deg[i] != 0) s = i;

	euler(s);
	if(cnt != n){
		cout << "some beads may be lost\n";
		return;
	}

	reverse(AI(ans));
	for(int i = 0; i < n; ++i){ 
		cout << ans[i].ff << ' ' << ans[i].ss << '\n';
	}
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t; cin >> t;
	for(int i = 1; i <= t; ++i){
		cout << "Case #" << i << "\n";
		solve();
		if(i < t) cout << "\n";
	}
	return 0;
}
