#include<iostream>
using namespace std;

int main(){
	int p,k,n,b,sum;
	cin>>p;
	for(int i=0;i<p;i++){
		cin>>k>>b>>n;
		sum=0;
		while(n>0){
			sum+=(n%b)*(n%b);
			n/=b;
		}
		cout<<k<<' '<<sum<<'\n';
	}
	return 0;
}