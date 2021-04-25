#include<iostream>
using namespace std;

int main(){
	int a,b,n,i;
	while(cin>>a>>b>>n){
		cout<<a/b<<'.';
		for(i=0;i<n;i++){
			a=(a%b)*10;
			cout<<a/b;
		}
		cout<<endl;
	}
	return 0;
}