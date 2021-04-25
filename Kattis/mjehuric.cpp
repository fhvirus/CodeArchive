#include<iostream>
#include<algorithm>
using namespace std;

int main(){
	short val[5];
	for(int i=0;i<5;i++){
		cin>>val[i];
	}
	for(int i=4;i>=0;i--){
		for(int j=0;j<i;j++){
			if(val[j]>val[j+1]){
				swap(val[j],val[j+1]);
				for(int k=0;k<5;k++){
					cout<<val[k]<<' ';
				}
				cout<<'\n';
			}
		}
	}
	return 0;
}