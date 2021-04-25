#include<iostream>
#include<vector>
using namespace std;
/*
int b[4][4];

int main(){
	for(int i=0;i<16;i++)cin>>b[i/4][i];
	int n;
	cin>>n;
	vector<int> o[4];
	if(n==0){
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				if(b[i][j]){
					if(b[i][j]==o[i].back()){
						o[i].back()*=2;
					}else o[i].push_back(b[i][j]);
				}
			}
		}
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				b[i][j]=(j>o[i].size()?0:o[i][j]);
			}
		}
	}
	for(int i=0;i<4;i++){
		for(auto j:b[i])cout<<j<<' ';
		cout<<'\n';
	}
	return 0;
}
*/