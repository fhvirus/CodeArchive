#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int r,c;
	cin>>r>>c;
	char b[r][c];
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			cin>>b[i][j];
		}
	}
	int ans[5]={0,0,0,0,0};
	for(int i=0;i<r-1;i++){
		for(int j=0;j<c-1;j++){
			if(b[i][j]!='#'&&
				b[i][j+1]!='#'&&
				b[i+1][j]!='#'&&
				b[i+1][j+1]!='#')
			ans[(b[i][j]=='X')+
				(b[i][j+1]=='X')+
				(b[i+1][j]=='X')+
				(b[i+1][j+1]=='X')]++;
		}
	}
	for(auto i:ans)cout<<i<<'\n';
	return 0;
}