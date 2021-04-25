#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){
	int n, c;
	string name, finish, birth;
	cin>>n;
	while(n--){
		cin>>name>>finish>>birth>>c;
		if(finish >= "2010/01/01"){
			cout<<name<<" eligible\n";
			continue;
		}else if(birth >= "1991/01/01"){
			cout<<name<<" eligible\n";
			continue;
		}else if(c > 40){
			cout<<name<<" ineligible\n";
			continue;
		}else{
			cout<<name<<" coach petitions\n";
		}
	}
	return 0;
}