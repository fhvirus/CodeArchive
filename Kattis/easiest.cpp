#include<iostream>
using namespace std;

int digsum(int n){
	int sum=0;
	while(n>0)sum+=n%10,n/=10;
	return sum;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,i;
	while(cin>>n&&n){
		for(i=11;digsum(n*i)!=digsum(n);i++);
		cout<<i<<'\n';
	}
	return 0;
}