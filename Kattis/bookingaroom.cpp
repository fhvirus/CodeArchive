#include<iostream>
#include<algorithm>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int r, n;
	cin>>r>>n;
	if(r==n){
		cout<<"too late";
	}else if(n == 0){
		cout<<1;
	}else{
		bool b[r];
		int tmp;
		fill(b, b+r, 0);
		for(int i = 0; i < n; i++){
			cin>>tmp;
			b[tmp-1] = 1;
		}
		for(int i = 0; i < r; i++){
			if(!b[i]){
				cout<<i+1;
				break;
			}
		}
	}
	return 0;
}