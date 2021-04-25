#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

#define MAXN 200000
#define MAXLOGN 22

int anc[MAXN][MAXLOGN];
vector<int> people[MAXN];
int dep[MAXN],pa[MAXN];

void dfs(int n,int p){
	dep[n]=dep[p]+1;
	pa[n]=p;
	for(auto i: people[n]){
		if(!dep[i])dfs(i,n);
	}
	return;
}

int main(){
	int n,q,a,b;
	cin>>n>>q;
	for(int i=0;i<n-1;i++){
		cin>>a>>b;
		people[a].push_back(b);
		people[b].push_back(a);
	}
	dfs(1,0);
	//anc[1][0]=0;
	for(int i=1;i<=n;i++){
		anc[i][0]=pa[i];
	}
	for(int i=0;i+1<MAXLOGN;i++){
		for(int j=1;j<=n;j++){
			anc[j][i+1]=anc[anc[j][i]][i];
		}
	}
	for(int i=0;i<q;i++){
		cin>>a>>b;
		if(dep[a]<dep[b]) swap(a,b);
		int k=0;
		for(int j=dep[a]-dep[b];j>0;j/=2){
			if(j%2==1)
				a=anc[a][k];
			k++;
		}
		if(a==b){
			cout<<a<<endl;
		}else{
			for(int i=MAXLOGN-1;i>=0;i--){
				if(anc[a][i]!=anc[b][i]){
					a=anc[a][i];
					b=anc[b][i];
				}
			}
			cout<<anc[a][0]<<endl;
		}
	}
	return 0;
}