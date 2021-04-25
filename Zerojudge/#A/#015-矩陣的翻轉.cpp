#include<iostream>
using namespace std;

int main(){
	int x,y,i,j;
	while(cin>>x>>y){
		int table[x][y];
		for(i=0;i<x;i++){
			for(j=0;j<y;j++){
				cin>>table[i][j];
			}
		}
		for(i=0;i<y;i++){
			for(j=0;j<x;j++){
				cout<<table[j][i];
				if(j!=x-1) cout<<' ';
			}
			cout<<endl;
		}
	}
	return 0;
}