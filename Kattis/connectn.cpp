#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,w,h,bs=0,rs=0;
	cin>>n>>w>>h;
	char b[h][w];
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			cin>>b[i][j];
			if(b[i][j]=='B')bs++;
			if(b[i][j]=='R')rs++;
		}
	}
	if(bs<n&&rs<n){
		cout<<"NONE";
		return 0;
	}
	//check vertical
	if(h>=n){
		int bline,rline
	}
	//check horizontal
	if(w>=n){

	}
	//check /
	//check \\ 
	if(h>=n&&w>=n){

	}
	return 0;
}