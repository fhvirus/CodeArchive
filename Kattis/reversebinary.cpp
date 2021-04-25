#include<iostream>
using namespace std;

int main(){
	int n,m=0;
	cin>>n;
	while(n){
		m<<=1;
		m|=n%2;
		n>>=1;
	}
	cout<<m;
	return 0;
}