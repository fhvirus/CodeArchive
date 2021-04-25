#include<iostream>
#include<set>
#include<vector>
#include<algorithm>
#include<bitset>
#include<utility>

#define pb push_back

using namespace std;

bitset<200005> con;
vector<int> link[200005];

void dfs(int p){
	con[p]=1;
	for(auto i:link[p]){
		if(!con[i])dfs(i);
	}
	return;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,m,a,b;
	bool had1=false;
	cin>>n>>m;
	while(m--){
		cin>>a>>b;
		if(a==1||b==1)had1=true;
		link[a].pb(b);
		link[b].pb(a);
	}
	dfs(1);
	if(!had1){
		for(int i=2;i<=n;i++)cout<<i<<'\n';
	}
	else{
		bool connected=true;
		for(int i=2;i<=n;i++){
			if(!con[i]){
				connected=false;
				cout<<i<<'\n';
			}
		}
		if(connected)cout<<"Connected\n";
	}
	return 0;
}