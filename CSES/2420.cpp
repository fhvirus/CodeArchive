#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const int MOD = 1e9 + 7;
const int kP = 31;
int mad(int u, const int& v) {
	u += v - MOD;
	u += MOD & (u >> 31);
	return u;
}
int mul(const int& u, const int& v) {
	return static_cast<int64_t>(u) * v % MOD;
}
int mow(int x, int e) {
	int r = 1;
	while (e) {
		if (e & 1) r = mul(r, x);
		x = mul(x, x);
		e >>= 1;
	}
	return r;
}

struct BIT {
	int n; std::vector<int> val;
	BIT (int _n): n(_n), val(_n + 1, 0) {}
	void modify(int p, int v) {
		for (; p <= n; p += p & -p)
			val[p] = mad(val[p], v);
	}
	int query(int p) {
		int res = 0;
		for (; p > 0; p -= p & -p)
			res = mad(res, val[p]);
		return res;
	}
	int query(int l, int r) { return mad(query(r), MOD - query(l - 1)); }
};

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	int n, m;
	std::cin >> n >> m;

	std::string s;
	std::cin >> s;
	s = ' ' + s;

	std::vector<int> pw(n + 1), wp(n + 1);
	pw[0] = 1;
	for (int i = 1; i <= n; ++i) pw[i] = mul(pw[i - 1], kP);
	wp[n] = mow(pw[n], MOD - 2);
	for (int i = n; i >= 1; --i) wp[i - 1] = mul(wp[i], kP);

	BIT forward(n), bakward(n);
	for (int i = 1; i <= n; ++i) {
		forward.modify(i, mul(s[i] - 'a', pw[i - 1]));
		bakward.modify(i, mul(s[i] - 'a', pw[n - i]));
	}

	for (int t, i = 0; i < m; ++i) {
		std::cin >> t;
		if (t == 1) {
			int k; char x;
			std::cin >> k >> x;
			int d = mad(x, MOD - s[k]);
			s[k] = x;
			forward.modify(k, mul(d, pw[k - 1]));
			bakward.modify(k, mul(d, pw[n - k]));
		} else {
			int a, b;
			std::cin >> a >> b;
			int hash_forward = mul(forward.query(a, b), wp[a - 1]);
			int hash_bakward = mul(bakward.query(a, b), wp[n - b]);
			std::cout << (hash_forward == hash_bakward ? "YES\n" : "NO\n");
		}
	}

	return 0;
}
