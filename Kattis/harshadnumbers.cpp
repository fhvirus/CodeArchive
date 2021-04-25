#include<iostream>
using namespace std;

int d(int n){
	int r=0;
	while(n>0)r+=n%10,n/=10;
	return r;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	while(n%d(n))n++;
	cout<<n;
}