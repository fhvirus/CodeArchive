#include<iostream>
#include<string>
using namespace std;

int main(){
	string in;
	cin>>in;
	int ans=0;
	for(int i=0;i<in.length();i++){
		if(in[i]!="PER"[i%3])ans++;
	}
	cout<<ans;
	return 0;
}