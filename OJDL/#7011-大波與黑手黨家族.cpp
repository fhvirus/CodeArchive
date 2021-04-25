#include<iostream>
#include<vector>
using namespace std;

#define MAXN 1000010

vector<int> people[MAXN];
vector<int> prelist;
int pre[MAXN],first[MAXN],cnt=0;

void dfs(int n){
	pre[n]=++cnt;
	prelist.push_back(n);
	for(auto i: people[n]){
		if(!pre[i]){
			dfs(i);
			prelist.push_back(n);
		}
	}
	return;
}

int main(){
	int n,q;
	cin>>n>>q;
	int a,b;
	for(int i=0;i<n-1;i++){
		cin>>a>>b;
		people[a].push_back(b);
		people[b].push_back(a);
	}
	dfs(1);
	for(int i=0;i<prelist.size();i++){
		cout<<prelist[i]<<' ';
	}
	return 0;
}