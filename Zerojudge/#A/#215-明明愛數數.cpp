#include<iostream>
using namespace std;

int main(){
	int n,m,i,s;
	while(cin>>n>>m){
		for(s=n,i=1;s<=m;s+=n+i,i++){}
		cout<<i<<endl;
	}
	return 0;
}