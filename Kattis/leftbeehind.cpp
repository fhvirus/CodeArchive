#include<iostream>
using namespace std;

int main(){
	int n,m;
	while((cin>>n>>m) && (n!=0||m!=0)){
		if(n+m==13)cout<<"Never speak again.\n";
		else if(n > m)cout<<"To the convention.\n";
		else if(n < m)cout<<"Left beehind.\n";
		else cout<<"Undecided.\n";
	}
	return 0;
}