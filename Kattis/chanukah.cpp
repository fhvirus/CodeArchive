#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int P,k,n;
	cin>>P;
	while(P--){
		cin>>k>>n;
		cout<<k<<' '<<n*(n+1)/2+n<<'\n';
	}
	return 0;
}