#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,q,cmd,a,b;
	cin>>n>>q;
	int c[n];
	for(auto &i:c)cin>>i;
	while(q--){
		cin>>cmd>>a>>b;
		if(cmd==1)c[a-1]=b;
		else cout<<(c[a-1]>c[b-1]?c[a-1]-c[b-1]:c[b-1]-c[a-1])<<'\n';
	}
	return 0;
}