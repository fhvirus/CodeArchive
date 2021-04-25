#include<iostream>
#include<vector>
using namespace std;

#define eek ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
vector<int> V[800];
bool vis[800];

void init(int n){
	static int i;
	for(i = 0; i < n; i++){
		V[i].clear();
		vis[i] = false;
	}
	return;
}

void dfs(int a){
	vis[a] = true;
	for(auto i: V[a]){
		if(!vis[i])
			dfs(i);
	}
}

void solve(int n, int m){
	init(n);
	static int a, b, i;
	for(i = 0; i < m; i++){
		cin >> a >> b;
		V[a-1].push_back(b-1);
	}
	cin >> a >> b;
	dfs(a-1);
	cout << (vis[b-1] ? "Yes!!!\n" : "No!!!\n");
}

int main(){eek
	int n, m;
	while(cin >> n >> m)
		solve(n, m);
	return 0;
}