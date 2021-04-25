#include<iostream>
#include<string>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	string in;
	cin.ignore();
	while(n--){
		getline(cin,in);
		if(in.substr(0,10)=="Simon says"){
			in.erase(in.begin(),in.begin()+10);
			cout<<in<<'\n';
		}
	}
	return 0;
}