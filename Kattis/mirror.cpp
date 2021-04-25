#include<iostream>
using namespace std;

#define owo ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

char image[20][20];

int main(){owo
	int T, r, c;
	cin>>T;
	for(int k = 1; k <= T; k++){
		cout<<"Test "<<k<<'\n';
		cin>>r>>c;
		for(int i = 0; i < r; i++){
			for(int j = 0; j < c; j++){
				cin>>image[i][j];
			}
		}
		for(int i = r-1; i >= 0; i--){
			for(int j = c-1; j >= 0; j--){
				cout<<image[i][j];
			}
			cout<<'\n';
		}
	}
	return 0;
}