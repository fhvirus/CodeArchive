#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

char b[20][20];

int main(){OW0
	int r, c;
	cin>>r>>c;
	string cur, mn = "zzzzzzzzzzzzzzzzzzzzz";
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			cin>>b[i][j];
		}
	}
	for(int i = 0; i < r; i++){
		cur = "";
		for(int j = 0; j < c; j++){
			if(b[i][j] == '#'){
				if(cur < mn){
					if(cur.size()>1)mn = cur;
				}
				cur = "";
			}else{
				cur += b[i][j];
			}
		}
		if(cur < mn){
			if(cur.size()>1)mn = cur;
		}
	}
	for(int i = 0; i < c; i++){
		cur = "";
		for(int j = 0; j < r; j++){
			if(b[j][i] == '#'){
				if(cur < mn){
					if(cur.size()>1)mn = cur;
				}
				cur = "";
			}else{
				cur += b[j][i];
			}
		}
		if(cur < mn){
			if(cur.size()>1)mn = cur;
		}
	}
	cout<<mn;
	return 0;
}