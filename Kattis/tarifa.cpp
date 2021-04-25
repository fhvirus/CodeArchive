#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int x,n,p,ans=0;
	cin>>x>>n;
	for(int i=0;i<n;i++){
		cin>>p;
		ans+=x-p;
	}
	ans+=x;
	cout<<ans<<'\n';
	return 0;
}