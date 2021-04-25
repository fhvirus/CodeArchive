#include<iostream>
#include<vector>
using namespace std;

const int N = 500;
int t, n, m, match[N], ans, vis[N], jizz;
vector<int> adj[N];

bool dfs(int u){
	if(vis[u] == jizz) return false;
	vis[u] = jizz;
	for(int v: adj[u])
		if(match[u] == -1 or dfs(match[v])){
			match[u] = v, match[v] = u;
			return true;
		}
	return false;
}

int main(){
	cin >> t;
	for(; t; --t){
		cin >> n >> m; ans = 0; jizz = 0;
		for(int i = 0; i < n; ++i){
			adj[i].clear();
			match[i] = -1;
			vis[i] = 0;
		}
		for(int i = 0, a, b; i < m; ++i){
			cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		// for(int i = 0; i < n; ++i){
		// 	if(match[i] != -1) continue;
		// 	for(int j: adj[i])
		// 		if(match[j] == -1)
		// 			match[i] = j, match[j] = i, ans ++;
		// }
		for(int i = 0; i < n; ++i)
			if(match[i] == -1)
				++jizz, ans += dfs(i);
		cout << ans/2 << '\n';
	}
}