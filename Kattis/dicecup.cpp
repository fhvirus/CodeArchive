#include<iostream>
#include<string>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,m;
	cin>>n>>m;
	if(n>m)n^=m^=n^=m;
	for(int i=n+1;i<=m+1;i++)cout<<i<<'\n';
	return 0;
}