#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int gcd(int a, int b){
	int c;
	if(a > b)c=a,a=b,b=c;
	while(c = a % b){
		a = b, b = c;
	}
	return b;
}

int main(){OW0
	int n, f, cur;
	cin>>n>>f;
	while(--n){
		cin>>cur;
		cout<<f/gcd(f, cur)<<'/'<<cur/gcd(f, cur)<<'\n';
	}
	return 0;
}