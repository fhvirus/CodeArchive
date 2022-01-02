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
		v.emplace_back(b, a);
	}
	sort(begin(v), end(v));

	int ans = 0, cur = 0;
	for (auto &[b, a]: v) {
		if (a < cur) continue;
		++ans;
		cur = b;
	}
	cout << ans << '\n';

	return 0;
}
