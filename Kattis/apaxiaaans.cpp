#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string in;
	cin>>in;
	char tmp;
	for(int i=0;i<in.length();i++){
		tmp=in[i];
		cout<<tmp;
		while(in[i+1]==tmp)i++;
	}
	return 0;
}