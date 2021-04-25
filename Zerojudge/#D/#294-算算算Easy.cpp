#include<iostream>
using namespace std;

int main(){
	int n,m;
	while(cin>>n>>m){
		cout<<n*(n+1)*m*(m+1)/4<<endl;
	}
}