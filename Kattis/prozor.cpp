#include<iostream>
using namespace std;

int main(){
	int x,y,r;
	cin>>x>>y>>r;
	char win[x][y];
	for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){
			cin>>win[i][j];
		}
	}
	
	int tmp,maxi=0,maxj=0,mx=0;
	for(int i=0;i<x-r+1;i++){
		for(int j=0;j<y-r+1;j++){
			
			tmp=0;
			for(int m=0;m<r-2;m++){
				for(int n=0;n<r-2;n++){
					if(win[i+m+1][j+n+1]=='*')tmp++;
				}
			}
			if(tmp>mx){
				mx=tmp;
				maxi=i;
				maxj=j;
			}
		}
	}

	
	win[maxi][maxj]='+';
	win[maxi+r-1][maxj]='+';
	win[maxi][maxj+r-1]='+';
	win[maxi+r-1][maxj+r-1]='+';

	for(int i=maxi+1;i<maxi+r-1;i++){
		win[i][maxj]='|';
		win[i][maxj+r-1]='|';
	}

	for(int j=maxj+1;j<maxj+r-1;j++){
		win[maxi][j]='-';
		win[maxi+r-1][j]='-';
	}

	cout<<mx<<'\n';
	for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){
			cout<<win[i][j];
		}
		cout<<'\n';
	}
	
	return 0;
}