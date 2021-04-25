#include<iostream>
using namespace std;

int main(){
	long long int n,ans;
	while(cin>>n){
		ans=0;
		while(n>=5){
			n/=5;
			ans+=n;
		}
		cout<<ans<<endl;
	}
	return 0;
}