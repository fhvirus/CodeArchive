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

void solve(int n, int m){
	vector<vector<pii>> adj(n + 2, vector<pii>());
	for(int i = 0; i < m; ++i){
		int l, r, v; string c;
		cin >> l >> r >> c >> v;
		r = l + r;
		if(c == "gt") adj[r].pb(l-1, -(v+1));
		else adj[l-1].pb(r, v-1);
	}
	for(int i = 0; i <= n; ++i) adj[n+1].pb(i, 0);

	vector<int> dis(n + 2, 1e9); dis[n+1] = 0;
	vector<int> inq(n + 2, 0); inq[n+1] = 1;
	vector<int> tot(n + 2, 0);
	queue<int> q; q.push(n+1);

	while(!q.empty()){
		int u = q.front(); q.pop(); inq[u] = false;
		for(auto [v, c]: adj[u])
			if(chmin(dis[v], dis[u] + c) and !inq[v]){
				inq[v] = true, ++tot[v], q.push(v);
				if(tot[v] >= n + 2){
					puts("successful conspiracy");
					return;
				}
			}
	}
	puts("lamentable kingdom");
	return;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n, m;
	while(cin >> n && n){
		cin >> m;
		solve(n, m);
	}
	return 0;
}
