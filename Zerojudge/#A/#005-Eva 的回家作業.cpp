#include<iostream>
using namespace std;

int main(){
	int x,a[4],i,j;
	cin>>x;
	for(i=0;i<x;i++){
		for(j=0;j<4;j++){
			cin>>a[j];
		}
		for(j=0;j<4;j++){
			cout<<a[j]<<" ";
		}
		if(a[1]-a[0]==a[2]-a[1]&&a[2]-a[1]==a[3]-a[2]){
			cout<<a[3]+a[1]-a[0]<<endl;
		} else {
			cout<<a[3]*a[1]/a[0]<<endl;
		}
	}
	return 0;
}