#include<iostream>
using namespace std;

int main(){
	int a,b,c,m;
	while(cin>>a>>b>>c){
		m=(a+b+c>a*b+c?a+b+c:a*b+c);
		m=(m>a+b*c?m:a+b*c);
		m=(m>a*b*c?m:a*b*c);
		m=(m>(a*10+b)+c?m:(a*10+b)+c);
		m=(m>(a*10+b)*c?m:(a*10+b)*c);
		m=(m>(b*10+c)+a?m:(b*10+c)+a);
		m=(m>(b*10+c)*a?m:(b*10+c)*a);
		cout<<m<<endl;
	}
}