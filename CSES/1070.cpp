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
 
	int n; cin >> n;
	if (n == 1) {
		cout << 1 << endl;
		return 0;
	}
	if (n <= 3) {
		cout << "NO SOLUTION\n";
		return 0;
	}
 
	for (int k = (n + 1) / 2, l = n / 2; k >= 1; --k) {
		cout << k << ' ';
		if (k + l <= n and k + l != (n + 1) / 2)
			cout << k + l << ' ';
	}
 
	return 0;
}
