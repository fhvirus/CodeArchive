#include<iostream>
using namespace std;

int main(){
	int n,k;
	while(cin>>n>>k){
		if(n==0){
			cout<<"Ok!"<<endl;
		} else if(k==0||n%k>0){
			cout<<"Impossib1e!"<<endl;
		} else {
			cout<<"Ok!"<<endl;
		}
	}
	return 0;
}