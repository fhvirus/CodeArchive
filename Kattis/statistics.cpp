#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int T=0, n, mx, mn, tmp;
	while(cin>>n){
		cout<<"Case "<< ++T <<": ";
		mn = 1000005, mx = -1000005;
		for(int i = 0; i < n; i++){
			cin>>tmp;
			if(tmp < mn)mn = tmp;
			if(tmp > mx)mx = tmp;
		}
		cout<<mn<<' '<<mx<<' '<<(mx-mn)<<'\n';
	}
	return 0;
}