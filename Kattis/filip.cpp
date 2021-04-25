#include<iostream>
#include<string>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int a,b;
	cin>>a>>b;
	a=a-99*((a/100)-(a%10));
	b=b-99*((b/100)-(b%10));
	cout<<(a>b?a:b)<<'\n';
	return 0;
}