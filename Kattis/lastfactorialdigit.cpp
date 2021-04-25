#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t,n;
	cin>>t;
	for(int i=0;i<t;i++){
		cin>>n;
		for(int j=n-1;j>1;j--)n=(n*j)%10;
		cout<<n<<'\n';
	}
	return 0;
}