#include<iostream>
#include<iomanip>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	long long t,lt;
	double g,lg,a;
	cin>>lt>>lg;
	for(int i=1;i<n;i++){
		cin>>t>>g;
		a+=(g+lg)*(t-lt)/2000;
		lg=g,lt=t;
	}
	cout<<setprecision(6)<<fixed<<a;
	return 0;
}