#include<iostream>
#include<string>
using namespace std;

int main(){
	int n,cnt=1;
	string name[15],a[8],b[8];
	while(cin>>n&&n){
		cout<<"SET "<<cnt++<<endl;
		for(int i=0;i<n;i++){
			cin>>name[i];
		}
		for(int i=0;i<n;i+=2){
			cout<<name[i]<<endl;
		}
		for(int i=n-n%2-1;i>0;i-=2){
			cout<<name[i]<<endl;
		}
	}
	return 0;
}