#include<iostream>
using namespace std;

int main(){
	string a,b;
	cin>>a>>b;
	for(int i=0;i<a.size();i++){
		if(i%2==0){
			a[i]=((a[i]-'A')-(b[i]-'A')+26)%26+'A';
		}else{
			a[i]=((a[i]-'A')+(b[i]-'A')+26)%26+'A';
		}
	}
	cout<<a;
	return 0;
}