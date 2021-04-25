#include<iostream>
#include<iomanip>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string in;
	cin>>in;
	double A=0,a=0,_=0,s=0,S=0;
	for(int i=0;i<in.length();i++)(in[i]=='_'?_:(in[i]<='Z'&&in[i]>='A'?A:(in[i]<='z'&&in[i]>='a'?a:s)))++;
	S=A+a+_+s;
	cout<<setprecision(16)<<fixed<<_/S<<'\n'<<a/S<<'\n'<<A/S<<'\n'<<s/S;
	return 0;
}