#include<iostream>
#include<iomanip>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n;
	double a, b, c, d;
	c = d = 0;
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> a >> b;
		c += a, d += b;
	}
	double ans = d / (c * 60);
	if(ans <= 1) cout << "measurement error";
	else cout <<setprecision(9)<<fixed<< d / (c * 60);
	return 0;
}