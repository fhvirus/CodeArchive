#include<iostream>
#include<algorithm>
#include<iomanip>
using namespace std;
const int N = 5e5;
const double EPS = 1e-10;
int n, x[N], v[N];
inline bool check(double t){
	double curmax = -2e20;
	for(int i = 0; i < n; ++i){
		double cur = x[i] + v[i] * t;
		if(v[i] < 0){
			if(curmax > cur) return true;
		} else {
			curmax = max(curmax, cur);
		}
	}
	return false;
}
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n;
	for(int i = 0; i < n; ++i) cin >> x[i] >> v[i];
	double l = 0, r = 2e9, m;
	while(r - l > EPS){
		m = (l + r) / 2;
		if(check(m)) r = m;
		else l = m;
	}
	if(r == 2e9) cout << -1;
	else cout << setprecision(10) << fixed << l;
}