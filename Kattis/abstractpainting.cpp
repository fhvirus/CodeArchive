#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
const int M = 1e9 + 7;

long long int pow(long long int m, long long int n){
	if(n == 0)return 1;
	if(n == 1)return m % M;
	long long int ans = pow(m, n/2) * pow(m, n/2) % M;
	if(n % 2){
		return ans * m % M;
	}else{
		return ans;
	}
}

int main(){OW0
	long long int T, x, y;
	cin>>T;
	while(T--){
		cin>>x>>y;
		cout << (pow(2, x * y) * pow(3, x + y)) % M <<'\n';
	}
	return 0;
}