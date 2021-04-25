#include<iostream>
using namespace std;

int main(){
	int n,a,f;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a>>f;
		for(int i=0;i<f;i++){
			for(int j=1;j<a;j++){
				for(int k=0;k<j;k++)
					cout<<j;
				cout<<endl;
			}
			for(int j=a;j>0;j--){
				for(int k=0;k<j;k++)
					cout<<j;
				cout<<endl;
			}
			cout<<endl;
		}
	}
	return 0;
}