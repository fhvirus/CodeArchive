#include<iostream>
#include<cmath>
using namespace std;

int main(){
	int a,b;
	while(cin>>a>>b&&(a!=0||b!=0)){
		cout<<floor(sqrt(b))-ceil(sqrt(a))+1<<endl;
	}
	return 0;
}