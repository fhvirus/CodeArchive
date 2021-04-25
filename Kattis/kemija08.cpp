#include<iostream>
using namespace std;

int main(){
	string n;
	getline(cin,n);
	for(int i=0;i<n.length();i++){
		if(n[i]=='a'||n[i]=='e'||n[i]=='i'||n[i]=='o'||n[i]=='u')n.erase(i,2);
	}
	cout<<n;
	return 0;
}