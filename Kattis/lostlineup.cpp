#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,tmp;
	cin>>n;
	int line[n];
	line[0]=1;
	for(int i=2;i<=n;i++){
		cin>>tmp;
		line[tmp+1]=i;
	}
	for(auto i:line)cout<<i<<' ';
	return 0;
}