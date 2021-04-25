#include<iostream>
#include<iomanip>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	double a, b, c, i, j, k;
	cin>>a>>b>>c>>i>>j>>k;
	double r = a / i;
	if(b / j < r)r = b / j;
	if(c / k < r)r = c / k;
	cout<<setprecision(6)<<fixed
		<< a - i * r <<' '
		<< b - j * r <<' '
		<< c - k * r <<'\n';
	return 0;
}