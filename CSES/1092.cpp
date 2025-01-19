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
 
	ll n; cin >> n;
	ll sum = n * (n + 1) / 2;
	if (sum & 1) {
		cout << "NO\n";
		return 0;
	}
	ll haf = sum / 2;
 
	ll sa = 0, sb = 0;
	vector<int> a, b;
	for (int i = 1; i <= n; ++i) {
		a.pb(i);
		sa += i;
	}
	while (sa - a.back() > haf) {
		sa -= a.back();
		sb += a.back();
		b.pb(a.back());
		a.pop_back();
	}
	ll num = sa - haf;
	if (num != 0) {
		swap(a.back(), a[num-1]);
		sa -= a.back();
		sb += a.back();
		b.pb(a.back());
		a.pop_back();
	}
	assert(sa == sb);
 
	cout << "YES\n";
	cout << a.size() << '\n';
	for (int &i: a) cout << i << ' ';
	cout << '\n';
	cout << b.size() << '\n';
	for (int &i: b) cout << i << ' ';
	cout << '\n';
 
	return 0;
}
