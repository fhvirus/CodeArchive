#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

#define eek ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
const double PI = 3.14159265358979323846;

int main(){eek
	int t;
	double n;
	cin >> t;
	while(t--){
		cin >> n;
		n *= 2;
		double theta = (PI - 2*PI/n)/2;
		cout <<setprecision(9)<<fixed<< tan(theta) << '\n';
	}
	return 0;
}