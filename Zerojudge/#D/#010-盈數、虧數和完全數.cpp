#include<iostream>
using namespace std;

int main(){
	int n,ans;
	while(cin>>n){
		ans=1;
		for(int i=2;i<n;i++){
			if(n%i==0)ans+=i;
		}
		cout<<(ans>n?"盈數":(ans<n?"虧數":"完全數"))<<endl;
	}
	return 0;
}