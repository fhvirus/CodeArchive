#include<iostream>
#include<vector>
using namespace std;

#define eek ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

vector<int> G[40001];
int color[40001];
bool isbipartite;
int n, m;

void dfs(int s){
	for(auto i: G[s]){
		if(!color[i]) color[i] = -color[s], dfs(i);
		else if(color[i] == color[s]){
			isbipartite = false;
			return;
		}
	}
}

int main(){eek
	int a, b;
	while(cin >> n >> m, n){
		isbipartite = true;
		for(int i = 1; i <= n; i++){
			G[i].clear(), color[i] = 0;
		}

		int a, b;
		for(int i = 0; i < m; i++){
			cin >> a >> b;
			G[a].push_back(b);
			G[b].push_back(a);
		}

		for(int i = 1; i <= n and isbipartite; i++){
			if(!color[i]) color[i] = 1, dfs(i);
		}
		cout << (isbipartite? "Yes\n" : "No\n");
	}
	return 0;
}