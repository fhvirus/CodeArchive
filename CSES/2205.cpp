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
 
vector<int> grayCode(int n) {
	if (n == 1)
		return vector<int>({0, 1});
 
	vector<int> code, edoc;
	code = grayCode(n - 1);
	edoc = code;
	reverse(AI(edoc));
	for (int &i: edoc) {
		i |= (1 << (n-1));
		code.pb(i);
	}
 
	return code;
}
 
signed main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
	int n; cin >> n;
 
	auto code = grayCode(n);
 
	for (int &i: code) {
		for (int j = 0; j < n; ++j)
			cout << (i >> j & 1);
		cout << '\n';
	}
 
	return 0;
}
