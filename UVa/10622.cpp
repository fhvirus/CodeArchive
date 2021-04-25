#include<iostream>
#include<cmath>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int f(int n){
	for(int i = 2; i < 50000; i++){
		if(pow( i, (int)(log10(fabs(n))/log10(fabs(i))+.01)) == n)
			return (int)(log10(fabs(n))/log10(fabs(i))+.01);
		if(pow(-i, (int)(log10(fabs(n))/log10(fabs(i))+.01)) == n)
			return (int)(log10(fabs(n))/log10(fabs(i))+.01);
	}
	return 1;
}

int main(){OW0
	int n;
	while(cin>>n and n)
		cout<<f(n)<<'\n';
	return 0;
}