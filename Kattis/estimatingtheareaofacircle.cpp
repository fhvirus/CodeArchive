#include<iostream>
#include<iomanip>
using namespace std;

#define owo ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
const double pi = 3.14159265358979;

int main(){owo
	double a, b, c;
	while(cin>>a>>b>>c){
		if(a==0&&b==0&&c==0)break;
		cout.precision(10);
		cout.width(11);
		cout<<a*a*pi<<' ';
		cout<<c/(b/4)*a*a<<'\n';
	}
	return 0;
}