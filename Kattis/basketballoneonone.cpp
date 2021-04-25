#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int a=0,b=0,i=0;
	string in;
	cin>>in;
	for(;i<in.length();i+=2)(in[i]=='A'?a:b)+=in[i+1];
	cout<<(a>b?'A':'B');
	return 0;
}