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

const int kN = 45, kM = 1995;
int m;
int deg[kN];
bool used[kM];
vector<pii> adj[kN];
vector<int> ans;

void add(int u, int v, int c){
	++m;
	used[c] = false;
	adj[u].pb(v, c);
	adj[v].pb(u, c);
	++deg[u]; ++deg[v];
}

void euler(int u){
	while(!adj[u].empty()){
		auto [v, c] = adj[u].back(); adj[u].pop_back();
		if(used[c]) continue;
		used[c] = true;
		euler(v);
		ans.pb(c);
		--m;
	}
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	while(true){
		int u, v, c; cin >> u >> v;
		if(u == 0 and v == 0) break;
		cin >> c;
		int s = min(u, v);
		ans.clear();
		for(int i = 0; i < kN; ++i){
			adj[i].clear();
			deg[i] = 0;
		}
		add(u, v, c);
		while(cin >> u >> v and u and v){
			cin >> c;
			add(u, v, c);
		}

		bool has = true;
		for(int i = 0; i < kN; ++i){
			if(deg[i] % 2 != 0){
				has = false;
				break;
			}
			sort(AI(adj[i]), [](pii a, pii b){ return a.ss > b.ss; });
		}
		euler(s);

		if(m != 0) has = false;

		if(!has) cout << "Round trip does not exist.\n\n";
		else{ 
			reverse(AI(ans));
			for(int i = 0; i < ans.size(); ++i)
				cout << ans[i] << " \n"[i == ans.size() - 1];
			cout << '\n';
		}
	}
	return 0;
}
