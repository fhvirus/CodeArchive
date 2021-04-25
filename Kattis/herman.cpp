#include<iostream>
#include<iomanip>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	double r;
	cin>>r;
	cout<<setprecision(6)<<fixed<<r*r*3.14159265358979<<'\n'<<r*r*2;
	return 0;
}