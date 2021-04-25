#include<iostream>
#include<iomanip>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int L;
	double C,w,l,ans=0;
	cin>>C>>L;
	for(int i=0;i<L;i++){
		cin>>w>>l;
		ans+=w*l;
	}
	ans*=C;
	cout<<setprecision(7)<<fixed<<ans<<'\n';
	return 0;
}