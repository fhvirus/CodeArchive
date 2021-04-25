#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,x;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>x;
		cout<<x<<(x%2?" is odd\n":" is even\n");
	}
	return 0;
}