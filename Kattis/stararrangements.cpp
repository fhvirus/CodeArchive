#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	cout<<n<<":\n";
	for(int i=2;i*2<=n+1;i++){
		if((n-i)%(i+i-1)==0)cout<<i<<','<<i-1<<'\n';
		if(n%(i+i-1)==0)cout<<i<<','<<i-1<<'\n';
		if(n%i==0)cout<<i<<','<<i<<'\n';
	}
	return 0;
}