#include<iostream>
#include<cmath>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,in,ans=0;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>in;
		ans+=(int)pow(in/10,in%10);
	}
	cout<<ans<<'\n';
	return 0;
}