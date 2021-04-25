#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	double q,y,ans=0;
	for(int i=0;i<n;i++){
		cin>>q>>y;
		ans+=q*y;
	}
	cout<<ans<<'\n';
	return 0;
}