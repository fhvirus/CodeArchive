#include<iostream>
#include<algorithm>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string in;
	int a,b,c;
	cin>>a>>b>>c>>in;
	for(int i=0;i<3;i++){
		cout<<(in[i]=='C'?max(a,max(b,c)):(in[i]=='A'?min(a,min(b,c)):a+b+c-max(a,max(b,c))-min(a,min(b,c))))<<' ';
	}
	return 0;
}