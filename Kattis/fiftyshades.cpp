#include<iostream>
#include<string>
#include<cctype>
using namespace std;

int main(){
	int n,ans=0;
	cin>>n;
	string in;
	while(n--){
		cin>>in;
		for(int i=0;i<in.size();i++)in[i]=tolower(in[i]);
		if(in.find("pink")!=string::npos||in.find("rose")!=string::npos){
			ans++;
		}
	}
	if(!ans)cout<<"I must watch Star Wars with my daughter";
	else cout<<ans;
	return 0;
}