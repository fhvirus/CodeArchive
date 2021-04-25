#include<iostream>
using namespace std;

int main(){
	int n[10005];
	n[0]=1,n[1]=1;
	for(int i=2;i<10005;i++)n[i]=(n[i-1]+n[i-2])%1000000007;
	int a;
	while(cin>>a)cout<<n[a]<<'\n';
	return 0;
}