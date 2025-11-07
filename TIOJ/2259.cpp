#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<int, int> pii;
#define ff first
#define ss second
#define pb emplace_back
#define AI(x) begin(x),end(x)
#ifdef OWO
#define debug(args...) LKJ("\033[1;32m[ " + string(#args) + " ]\033[0m", args)
template <class I> void LKJ(I&&x) { cerr << x << endl; }
template <class I, class...T> void LKJ(I&&x, T&&...t) { cerr << x << ", "; LKJ(t...); }
template <class I> void OI(I a, I b) { while (a < b) cerr << *a << " \n"[next(a) == b], ++a; }
#else
#define debug(...) 0
#define OI(...) 0
#endif

const int MOD = 1e9 + 7;
int mad(int u, int v) {
	u += v - MOD;
	u += MOD & (u >> 31);
	return u;
}
int mul(int u, int v) {
	return (ll) u * v % MOD;
}

typedef array<array<int, 3>, 3> Mat;
int eek[3][3]{
	{ 0, 1, 1 },
	{ 1, 1, 0 },
	{ 0, 2, 1 }
};
Mat mul(Mat a, Mat b) {
	Mat c;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j) {
			c[i][j] = 0;
			for (int k = 0; k < 3; ++k)
				c[i][j] = mad(c[i][j], mul(a[i][k], b[k][j]));
		}
	return c;
}

signed main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	ll L; cin >> L;
	--L;

	Mat r, x;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j) {
			r[i][j] = (i == j);
			x[i][j] = eek[i][j];
		}

	while (L) {
		if (L & 1) r = mul(r, x);
		x = mul(x, x);
		L >>= 1;
	}

	cout << r[0][1] << '\n';

	return 0;
}
