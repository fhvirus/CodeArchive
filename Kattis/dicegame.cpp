#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int a=0,b=0,tmp;
	for(int i=0;i<4;i++){cin>>tmp;a+=tmp;}
	for(int i=0;i<4;i++){cin>>tmp;b+=tmp;}
	cout<<(a>b?"Gunnar":(a<b?"Emma":"Tie"));
	return 0;
}