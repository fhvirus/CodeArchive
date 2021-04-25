#include<iostream>
#include<bitset>
#include<vector>
using namespace std;

bool graph[20][20];
vector<int> weak;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	while(cin>>n&&n!=-1){
		weak.clear();
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				cin>>graph[i][j];
			}
		}
		bool tmp;
		for(int i=0;i<n;i++){
			tmp=0;
			for(int j=0;j<n;j++){
				if(graph[i][j]){
					for(int k=0;k<n;k++){
						if(graph[i][k]&&graph[j][k])tmp=1;
					}
				}
			}
			if(!tmp)weak.push_back(i);
		}
		for(auto i: weak)cout<<i<<' ';
		cout<<'\n';
	}
	return 0;
}