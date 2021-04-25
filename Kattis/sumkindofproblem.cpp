#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int T, k, n;
	cin>>T;
	while(T--){
		cin>>k>>n;
		cout << k <<' '<< (n+1)*n/2 <<' '<< n*n <<' '<< (1 + n)*n <<'\n';
	}
	return 0;
}