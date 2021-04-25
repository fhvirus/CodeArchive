#include<iostream>
#include<string>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t=0,c=0,g=0;
	string in;
	cin>>in;
	for(int i=0;i<in.length();i++){
		if(in[i]=='T')t++;
		else if(in[i]=='C')c++;
		else if(in[i]=='G')g++;
	}
	cout<<t*t+c*c+g*g+(t<g?(t<c?t:c):(g<c?g:c))*7;
	return 0;
}