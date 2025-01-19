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
	vector<int> p(n);
	for (int &i: p)
		cin >> i;
 
	ll ans = 1e18;
	for (int s = 0; s < (1 << n); ++s) {
		ll sum = 0;
		for (int i = 0; i < n; ++i)
			if (s >> i & 1) sum += p[i];
			else sum -= p[i];
		ans = min(ans, (sum < 0 ? -sum : sum));
	}
	cout << ans << '\n';
 
	return 0;
}
