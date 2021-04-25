#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,a=1,b=0,c=1;
	cin>>n;
	if(!n){cout<<"1 0";return 0;}
	for(int i=1;i<n;i++){
		a=b,b=c,c=a+b;
	}
	cout<<b<<' '<<c;
	return 0;
}