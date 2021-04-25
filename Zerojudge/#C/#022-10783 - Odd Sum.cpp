#include<iostream>
using namespace std;

int main(){
	int t,a,b;
	cin>>t;
	for(int i=0;i<t;i++){
		cin>>a>>b;
		a+=1-(a%2);
		b-=1-(b%2);
		cout<<"Case "<<i+1<<": "<<(a+b)*((b-a)/2+1)/2<<endl;
	}
	return 0;
}