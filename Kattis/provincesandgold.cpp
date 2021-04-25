#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int g,s,c;
	cin>>g>>s>>c;
	int b=g*3+s*2+c;
	cout<<(b>=8?"Province or ":(b<=4?(b<=1?"":"Estate or "):"Duchy or "))<<(b>=6?"Gold":(b<=2?"Copper":"Silver"));
	return 0;
}