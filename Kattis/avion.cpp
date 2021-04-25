#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string in;
	int r=0;
	for(int i=0;i<5;i++){
		cin>>in;
		if(in.find("FBI")!=string::npos)r|=1<<i;
	}
	if(!r)cout<<"HE GOT AWAY!";
	else for(int i=0;i<5;i++)if(r&1<<i)cout<<i+1<<' ';
	return 0;
}