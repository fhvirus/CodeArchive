#include<iostream>
#include<vector>
using namespace std;

const int N = 1e5 + 1;
int t, n, a, b, da, db;
vector<int> adj[N];
int depth[N];

int dfs(int u, int p){
	int ans = u, eek;
	for(int v: adj[u]){
		if(v == p) continue;
		depth[v] = depth[u] + 1;
		eek = dfs(v, u);
		if(depth[eek] > depth[ans]) ans = eek;
	}
	return ans;
}
int dfs2(int u, int p, int target){
	for(int v: adj[u]){
		if(v == p) continue;
		if(v == target) return 1;
		int eek = dfs2(v, u, target);
		if(eek != -1) return eek + 1;
	}
	return -1;
}

inline void solve(){
	cin >> n >> a >> b >> da >> db;
	for(int i = 1; i <= n; ++i) adj[i].clear();
	for(int u, v, i = 1; i < n; ++i){
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	for(int i = 1; i <= n; ++i) depth[i] = 0;
	int jizz = dfs(1, 1);
	for(int i = 1; i <= n; ++i) depth[i] = 0;
	jizz = depth[dfs(jizz, jizz)];

	bool ans = true; // Bob
	if(jizz <= da * 2) ans = false;
	if(db <= da * 2) ans = false;
	if(dfs2(a, a, b) <= da) ans = false;

	cout << (ans ? "Bob" : "Alice") << '\n';
}

int main(){
	cin >> t; 
	while(t--) solve();
	return 0;
}