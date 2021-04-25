#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int a,n,ans=0;
	cin>>a;
	for(int i=0;i<a;i++){
		cin>>n;
		if(n<0)ans++;
	}
	cout<<ans<<endl;
	return 0;
}