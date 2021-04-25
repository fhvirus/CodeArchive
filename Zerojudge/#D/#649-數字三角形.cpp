#include<iostream>
using namespace std;

int main(){
	int n,i,j;
	while(cin>>n){
		if(n==0)break;
		for(i=0;i<n;i++){
			for(j=0;j<n-i-1;j++){
				cout<<'_';
			}
			for(j=0;j<i+1;j++){
				cout<<'+';
			}
			cout<<endl;
		}
		cout<<endl;
	}
	return 0;
}