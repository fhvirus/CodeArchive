#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	double a,b,c,d,s;
	cin>>a>>b>>c>>d;
	s=(a+b+c+d)/2;
	cout<<setprecision(15)<<sqrt((s-a)*(s-b)*(s-c)*(s-d));
	return 0;
}