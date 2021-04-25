#include<iostream>
using namespace std;

int  main(){
	unsigned int a,b,c;
	while(cin>>a>>b>>c){
		if(a>b&&a>c){
			cout<<(a>b+c?'A':(b>c?'B':'C'))<<endl;
		} else if(a<b&&b>c){
			cout<<(b>a+c?'B':(a>c?'A':'C'))<<endl;
		} else {
			cout<<(c>b+a?'C':(b>a?'B':'A'))<<endl;
		}
	}
}