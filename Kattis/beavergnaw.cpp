#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	double d,v;
	while(cin>>d>>v&&!(!d&&!v))cout<<setprecision(9)<<fixed<<cbrt(d*d*d-6*v/M_PI)<<'\n';
	return 0;
}