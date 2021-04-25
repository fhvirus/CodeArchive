#include<iostream>
using namespace std;

int main(){
	int t,n,m;
	cin>>t;
	for(int i=0;i<t;i++){
		cin>>n>>m;
		n-=2;m-=2;
		cout<<(n/3+(n%3==0?0:1))*(m/3+(m%3==0?0:1))<<endl;
	}
	return 0;
}