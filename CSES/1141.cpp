#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n; cin >> n;
	vector<int> k(n + 1, 0);
	for (int i = 1; i <= n; ++i)
		cin >> k[i];

	map<int, int> mp;
	int ans = 0, cur = 0;
	for (int i = 1; i <= n; ++i) {
		cur = max(cur, mp[k[i]]);
		ans = max(ans, i - cur);
		mp[k[i]] = i;
	}

	cout << ans << '\n';

	return 0;
}
