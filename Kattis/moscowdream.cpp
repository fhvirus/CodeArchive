#include<iostream>
using namespace std;

int main(){
	int a, b, c, n;
	cin>>a>>b>>c>>n;
	if(!a or !b or !c or n < 3){
		cout<<"NO";
	}else if(a + b + c < n){
		cout<<"NO";
	}else{
		cout<<"YES";
	}
	return 0;
}