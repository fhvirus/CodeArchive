#include<iostream>
#include<string>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string ans;
	int n;
	cin>>n>>ans;
	string A="ABC",B="BABC",G="CCAABB";
	int a,b,g;
	a=b=g=0;
	for(int i=0;i<n;i++){
		if(ans[i]==A[i%3])a++;
		if(ans[i]==B[i%4])b++;
		if(ans[i]==G[i%6])g++;
	}
	int m=(a>b?(a>g?a:g):(b>g?b:g));
	cout<<m<<'\n';
	if(a==m)cout<<"Adrian\n";
	if(b==m)cout<<"Bruno\n";
	if(g==m)cout<<"Goran\n";
	return 0;
}