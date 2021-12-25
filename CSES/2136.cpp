#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC target("popcnt")

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int n, k; cin >> n >> k;
	vector<int> a(n, 0);
	for (int &i: a) {
		char c;
		for (int j = 0; j < k; ++j) {
			cin >> c;
			i = i << 1 | (c - '0');
		}
	}

	int ans = k;
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			ans = min(ans, __builtin_popcount(a[i] ^ a[j]));

	cout << ans << '\n';

	return 0;
}
