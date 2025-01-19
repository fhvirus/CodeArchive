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
 
ll solve(ll k) {
	int cnt = 0;
	ll val = k;
	while (val) {
		++cnt;
		val /= 10;
	}
 
	ll ans = k * cnt;
	for (ll cur = 10; cur <= k; cur *= 10)
		ans -= cur - 1;
	return ans;
}
 
signed main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
 
	int q; cin >> q;
	while (q --> 0) {
		ll k; cin >> k;
		ll ans = 0;
		for (ll l = 1ll<<56; l > 0; l >>= 1)
			if (solve(ans + l) < k) ans += l;
		k -= solve(ans);
 
		vector<int> digit;
		ll val = ans + 1;
		while (val) {
			digit.pb(val % 10);
			val /= 10;
		}
		reverse(AI(digit));
		cout << digit[k - 1] << '\n';
	}
 
	return 0;
}
