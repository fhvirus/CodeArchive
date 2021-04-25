#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

int main(){
	double n;
	cin>>n;
	cout<<setprecision(6)<<fixed<<pow(n,1/n);
	return 0;
}