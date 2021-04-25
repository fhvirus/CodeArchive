#include<iostream>
using namespace std;

int main(){
	int i,j,count;
	while(cin>>i){
		j=1;
		while(i>1){
			j++; count=0;
			while(i%j==0){
				i/=j;
				count++;
			}
			if(count>0){
				cout<<j;
				if(count>1) cout<<"^"<<count;
				if(i>1) cout<<" * ";
				else cout<<endl;
			}
		}
	}
	return 0;
}