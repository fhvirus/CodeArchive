#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int T, n;
	cin>>T;
	while(T--){
		cin>>n;
		cout<< n/400 + (n%400? 1:0)<<'\n';
	}
	return 0;
}