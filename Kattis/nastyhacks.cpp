#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,r,e,c;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>r>>e>>c;
		cout<<(r>e-c?"do not advertise\n":(r==e-c?"does not matter\n":"advertise\n"));
	}
	return 0;
}