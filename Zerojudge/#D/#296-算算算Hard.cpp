#include<iostream>
using namespace std;

long long int hex(long long int n){
	if(n==1)return 1;
	return 3*n*(n-1)+1;
}

int main(){
	long long int n,ans,i;
	while(cin>>n){
		ans=0;
		for(i=0;i<n;i++){
			ans+=hex(n-i);
		}
		cout<<ans<<endl;
	}
	return 0;
}