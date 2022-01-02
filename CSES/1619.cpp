#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n; cin >> n;
	vector<pair<int, int>> v;
	for (int a, b, i = 0; i < n; ++i) {
		cin >> a >> b;
		v.emplace_back(a,  1);
		v.emplace_back(b, -1);
	}
	sort(begin(v), end(v));

	int ans = 0, cur = 0, lst = 0;
	for (auto &[t, w]: v) {
		if (lst != t) {
			ans = max(ans, cur);
			lst = t;
		}
		cur += w;
	}
	cout << ans << '\n';

	return 0;
}
