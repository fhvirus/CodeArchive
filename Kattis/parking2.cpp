#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m,t,mx,mn;
	cin>>n;
	while(n--){
		cin>>m;
		mx=0,mn=99;
		while(m--){
			cin>>t;
			if(t>mx)mx=t;
			if(t<mn)mn=t;
		}
		cout<<(mx-mn)*2<<'\n';
	}
	return 0;
}