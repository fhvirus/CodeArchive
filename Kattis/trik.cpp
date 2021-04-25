#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main(){
	string cmd;
	int ans;
	bool cup[3]={1,0,0};
	cin>>cmd;
	for(int i=0;i<cmd.length();i++){
		if(cmd[i]=='A')swap(cup[0],cup[1]);
		else if(cmd[i]=='B')swap(cup[1],cup[2]);
		else if(cmd[i]=='C')swap(cup[0],cup[2]);
	}
	for(int i=0;i<3;i++)if(cup[i])ans=i+1;
	cout<<ans;
	return 0;
}