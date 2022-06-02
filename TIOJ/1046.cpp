#include <bits/stdc++.h>
using namespace std;

inline int push(const int& a, const int& b)
{ return a ^ b ^ (b << 1) ^ (b >> 1); }

int solve(const int& n, const int& m, const vector<int>& a) {
	int b = 0, c = 0, ans = INT_MAX, mask = (1 << m) - 1;
	for (int f = 0; f <= mask; ++f) {
		int cur = __builtin_popcount(f);
		b = mask & push(a[0], f);
		c = f;
		for (int i = 1; i < n; ++i) {
			cur += __builtin_popcount(b);
			tie(b, c) = make_tuple((mask & push(a[i], b)) ^ c, b);
		}
		if (b == 0) ans = min(ans, cur);
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	string in;
	int n, m, ans;
	vector<int> a;

	while (8e7 /* is strong */) {
		getline(cin, in);
		if (in == "#") break;
		if (in == "") {
			ans = solve(n, m, a);
			if (ans == INT_MAX) cout << "Another Skeleton in the Ancient Tomb!\n";
			else cout << "Minimum Steps : " << ans << '\n';
			n = m = 0;
			a.clear();
		} else {
			n += 1;
			m = in.length();
			a.push_back(0);
			for (int j = 0; j < m; ++j)
				if (in[j] == 'O') a.back() |= (1 << j);
		}
	}

	return 0;
}
