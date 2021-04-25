#include<iostream>
using namespace std;

int fac(int n){
	if(n==0||n==1){
		cout<<"1 = ";
		return 1;
	} else {
		cout<<n<<" * ";
		return n*fac(n-1);
	}
}

int main(){
	int n;
	while(cin>>n){
		cout<<n<<"! = ";
		cout<<fac(n)<<endl;
	}
	return 0;
}