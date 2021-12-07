#include <iostream>
#include <vector>
#include <cmath>

void solve() {
	int n;
	std::cin >> n;

	std::vector<int> v(n);
	for (int &i: v)
		std::cin >> i;

	int ans = 0;
	for (int i = 0; i < n; ++i) {
		int mn = v[i];
		int mx = v[i];
		for (int j = i+1; j < n; ++j) {
			if (mn > v[j])
				mn = v[j];
			if (mx < v[j])
				mx = v[j];
			if (mx - mn == j - i and mx - mn == abs(v[j] - v[i]))
				++ans;
		}
	}

	std::cout << ans << '\n';
	return;
}

signed main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	int t;
	std::cin >> t;
	for (; t; --t)
		solve();

	return 0;
}
