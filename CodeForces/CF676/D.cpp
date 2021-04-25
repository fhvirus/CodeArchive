#pragma Ofast
#pragma loop-opt(on)
#define FOR(i, n) for(int i = 0; i < n; ++i)
#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ll long long
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 1e5;
ll t, x, y, c1, c2, c3, c4, c5, c6;

int main(){OW0
	cin >> t;
	for(; t; --t){
		cin >> x >> y;
		cin >> c1 >> c2 >> c3 >> c4 >> c5 >> c6;
		ll ans = (x < 0 ? c3 : c6) * abs(x) + (y < 0 ? c5 : c2) * abs(y);
		// x first
		{
			ll cost = (x < 0 ? c4 : c1) * abs(x);
			ll d = y - x;
			cost += (d < 0 ? c5 : c2) * abs(d);
			ans = min(ans, cost);
		}
		// y first
		{
			ll cost = (y < 0 ? c4 : c1) * abs(y);
			ll d = x - y;
			cost += (d < 0 ? c3 : c6) * abs(d);
			ans = min(ans, cost);
		}
		cout << ans << endl;
	}
	return 0;
}