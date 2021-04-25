#include<iostream>
#include<vector>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int r,c,zr,zc;
	cin>>r>>c>>zr>>zc;
	char b[r][c];
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			cin>>b[i][j];
		}
	}
	for(int i=0;i<r;i++){
		for(int ii=0;ii<zr;ii++){
			for(int j=0;j<c;j++){
				for(int jj=0;jj<zc;jj++){
					cout<<b[i][j];
				}
			}
			cout<<'\n';
		}
	}
	return 0;
}