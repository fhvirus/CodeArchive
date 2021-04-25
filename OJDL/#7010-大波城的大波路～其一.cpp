#include<iostream>
#include<vector>
#include<queue>
#include<utility>
#include<algorithm>
using namespace std;

#define MAX_N 10000
#define INF 1e18
#define int long long

vector<pair<int,int>> path[MAX_N];
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
int dist[MAX_N];

signed main(){
	int n,m;
	cin>>n>>m;
	int a,b,x;
	fill(dist,dist+n,INF);
	for(int i=0;i<m;i++){
		cin>>a>>b>>x;
		a--;b--;
		path[a].push_back({x,b});
		path[b].push_back({x,a});
	}

	pq.push({0,0});
	dist[0]=0;
	while(!pq.empty()){
		auto tmp=pq.top();
		pq.pop();
		if(tmp.first==INF||tmp.first>dist[tmp.second]) continue;
		for(auto i:path[tmp.second]){
			if(dist[i.second]>tmp.first+i.first){
				dist[i.second]=tmp.first+i.first;
				pq.push({dist[i.second],i.second});
			}
		}
	}
	for(int i=0;i<n;i++){
		cout<<dist[i]<<endl;
	}
	return 0;
}