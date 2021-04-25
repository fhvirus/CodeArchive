#include<iostream>
using namespace std;

int main(){
	int n,m;
	cin>>n>>m;
	if(n<=m)cout<<"Dr. Chaz will have "<<m-n<<(m-n>1?" pieces":" piece")<<" of chicken left over!";
	else cout<<"Dr. Chaz needs "<<n-m<<" more"<<(n-m>1?" pieces":" piece")<<" of chicken!";
	return 0;
}