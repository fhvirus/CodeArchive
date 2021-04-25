#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int a[6],b[6]={1,1,2,2,2,8};
	for(int i=0;i<6;i++){
		cin>>a[i];
		cout<<b[i]-a[i]<<' ';
	}
	return 0;
}