#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	int n, k;
	std::cin >> n >> k;

	std::vector<int> x(n);
	for (int i = 0; i < n; ++i)
		std::cin >> x[i];

	int64_t ans = 0;
	std::map<int, int> mp;
	int cnt_distinct = 0;
	for (int i = 0, j = 0; i <= n; ++i) {
		while (j < n) {
			if (mp[x[j]] == 0) {
				if (cnt_distinct == k) break;
				cnt_distinct += 1;
			}
			mp[x[j++]] += 1;
		}
		ans += j - i;
		mp[x[i]] -= 1;
		if (mp[x[i]] == 0) {
			cnt_distinct -= 1;
		}
	}

	std::cout << ans << '\n';
	return 0;
}
