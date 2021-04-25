#include<iostream>
using namespace std;

int main(){
	int n,i;
	while(cin>>n&&n!=0){
		for(i=1;i<n;i++){
			if(i%7!=0){
				cout<<i<<' ';
			}
		}
		cout<<endl;
	}
	return 0;
}