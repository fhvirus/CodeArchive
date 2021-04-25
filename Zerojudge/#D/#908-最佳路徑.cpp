#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;

#define eek ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

char st, a, b;
int m, mx=0, w;
int dist[26];
bool vis[26];
vector<pair<int, int>> V[26];
queue<int> Q;

void init(){
	for(int i = 0; i < 26; i++){
		dist[i] = 0;
		vis[i] = false;
		V[i].clear();
	}
}

void bfs(int a){
	vis[a] = true;
	dist[a] = 0;
	// Q.clear();
	Q.push(a);
	while(!Q.empty()){
		int i = Q.front(); Q.pop();
		vis[i] = true;
		for(auto j: V[i]){
			dist[j.first] = max(dist[j.first], dist[i] + j.second);
			Q.push(j.first);
		}
	}
}

int main(){eek
	cin >> st >> m;
	for(int i = 0; i < m; i++){
		cin >> a >> b >> w;
		V[a-'A'].push_back({b-'A', w});
	}
	bfs(st-'A');
	for(auto i: dist)
		if(mx < i) mx = i;
	cout << mx;
	return 0;
}