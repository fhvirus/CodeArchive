#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<int, int> pii;
#define ff first
#define ss second
#define AI(x) begin(x),end(x)
#define pb emplace_back
#ifdef OWO
#define debug(args...) LKJ("\033[1;32m[ " + string(#args) + " ]\033[0m", args)
template<class I> void LKJ(I&&x) { cerr << x << endl; }
template<class I, class...T> void LKJ(I&&x, T&&...t) { cerr << x << ", "; LKJ(t...); }
template<class I> void OI(I a, I b) { while (a < b) cerr << *a << " \n"[next(a) == b], ++a; }
#else
#define debug(...) 0
#define OI(...) 0
#endif
 
signed main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
	int t; cin >> t;
	while (t --> 0) {
		ll a, b; cin >> a >> b;
		// 2x + y = a
		// x + 2y = b
 
		// 3x + 3y = a + b
		// x - y = a - b
 
 
		if ((a + b) % 3 != 0) {
			cout << "NO\n";
			continue;
		}
 
		ll c = (a + b) / 3;
		ll d = a - b;
 
		if ((c + d) & 1) {
			cout << "NO\n";
			continue;
		}
 
		ll x = (c + d) / 2;
		ll y = (c - d) / 2;
 
		if (x < 0 or y < 0) {
			cout << "NO\n";
			continue;
		}
 
		cout << "YES\n";
	}
 
	return 0;
}
