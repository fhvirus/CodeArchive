#include<iostream>
using namespace std;

int main(){
	int L,x,p,n=0,cnt=0;
	string cmd;
	cin>>L>>x;
	for(int i=0;i<x;i++){
		cin>>cmd>>p;
		if(cmd=="enter"){
			if(n+p>L)cnt++;
			else n+=p;
		}else if(cmd=="leave")n-=p;
	}
	cout<<cnt;
	return 0;
}