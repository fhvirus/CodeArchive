#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

int main(){
	double n, m;
	cin>>n>>m;
	m = n - m;
	cout<<setprecision(10)<<fixed<<(m*m*M_PI)*100/(n*n*M_PI);
}