#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	double a, b, s, m, n;
	double hs, vs, spd, ang;
	while(cin>>a>>b>>s>>m>>n && (a||b||s||m||n)){
		hs = a * m / s;
		vs = b * n / s;
		ang = atan(vs / hs) * 180 / M_PI;
		spd = sqrt(hs * hs + vs * vs);
		cout<<setprecision(2)<<fixed<<ang<<' '<<spd<<'\n';
	}
	return 0;
}