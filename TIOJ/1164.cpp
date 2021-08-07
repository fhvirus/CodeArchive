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

#include "lib1164.h"

vector<vector<pii>> adj;
int ans;
int dfs(int u, int p){
	int dep = 0;
	for(auto [v, len]: adj[u]){
		if(v == p) continue;
		int d = dfs(v, u) + len;
		ans = max(ans, dep + d);
		dep = max(dep, d);
	}
	return dep;
}
int dia(MAP &mp){
	adj.assign(mp.m, vector<pii>());
	for(int i = 0; i < mp.k; ++i){
		adj[mp.x[i]].pb(mp.y[i], mp.len[i]);
		adj[mp.y[i]].pb(mp.x[i], mp.len[i]);
	}
	debug(adj);
	ans = 0;
	dfs(0, -1);
	return ans;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int N = init();
	//int mxi = 0, mni = 1;
	//if(query(mni, mxi)) swap(mni, mxi);
	//for(int i = 2; i < N; ++i){
	//	if(query(i, mxi)) mxi = i;
	//	else if(query(mni, i)) mni = i;
	//}
	vector<int> a(N); iota(AI(a), 0);
	auto [mxi, mni] = minmax_element(AI(a), query);

	MAP mn = getct(*mni);
	MAP mx = getct(*mxi);
	int mnl = dia(mn), mxl = dia(mx);
	answer(mxl, mnl);
	return 0;
}
