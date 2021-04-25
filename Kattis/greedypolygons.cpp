#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

int main(){
	int T;
	cin>>T;
	double n, l, d, g, ans;
	while(T--){
		cin>>n>>l>>d>>g;
		ans = (l * l * n) / (4 * tan(M_PI / n));
		ans += (d * g) * (d * g) * M_PI;
		ans += l * (d * g) * n;
		cout<< setprecision(14) << ans <<'\n';
	}
	return 0;
}