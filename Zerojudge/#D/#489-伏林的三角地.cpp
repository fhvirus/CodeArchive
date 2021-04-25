#include<iostream>
using namespace std;

int main(){
	int a,b,c,s;
	cin>>a>>b>>c;
	s=(a+b+c)/2;
	cout<<(s*(s-a)*(s-b)*(s-c))<<endl;
	return 0;
}