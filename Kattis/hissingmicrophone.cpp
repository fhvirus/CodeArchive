#include<iostream>
#include<string>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string m;
	cin>>m;
	bool hiss=0;
	for(int i=0;i<m.length()-1;i++)if(m[i]=='s'&&m[i+1]=='s')hiss=true;
	cout<<(hiss?"hiss":"no hiss");
	return 0;
}