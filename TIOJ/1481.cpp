// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

#ifndef OWO
#include "lib1481.h"
#else
void Init(){}
void Possible(){}
void Number(int n){ cout << n << '\n';}
void Finish(){}
#endif
const int N = 2002, K = 20002;

int n, k;
vector<pii> adj[N];
int ans[K], tot;

void dfs(int u){
	for(auto [v, i]: adj[u]){
		if(ans[i]) continue;
		ans[i] = ++tot;
		dfs(v);
	}
}

int32_t main(){
	Init();
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> k;
	for(int i = 1, u, v; i <= k; ++i){
		cin >> u >> v;
		adj[u].pb(v, i);
		adj[v].pb(u, i);
	}
	dfs(1);
	Possible();
	for(int i = 1; i <= k; ++i) Number(ans[i]);
	Finish();
	return 0;
}
