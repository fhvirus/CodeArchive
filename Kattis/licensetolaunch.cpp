#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,minday=0,minnum=1e9+7,junks;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>junks;
		if(junks<minnum)minday=i,minnum=junks;
	}
	cout<<minday;
	return 0;
}