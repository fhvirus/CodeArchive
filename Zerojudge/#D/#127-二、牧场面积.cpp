#include<iostream>
using namespace std;

int main(){
	long long int n;
	while(cin>>n){
		n/=2;
		cout<<(n%2==0?n*n/4:(n+1)*(n-1)/4)<<endl;
	}
	return 0;
}