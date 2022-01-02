#include <iostream>
#include <set>
using namespace std;

int main() {
	cin.tie(0) -> sync_with_stdio(0);
	cout.tie(0) -> sync_with_stdio(0);

	int n, m; cin >> n >> m;
	multiset<int> s;
	for (int h, i = 0; i < n; ++i) {
		cin >> h;
		s.emplace(h);
	}

	for (int t, i = 0; i < m; ++i) {
		cin >> t;
		auto it = s.upper_bound(t);
		if (it == begin(s)) {
			cout << -1 << '\n';
			continue;
		}
		it = prev(it);
		cout << *it << '\n';
		s.erase(it);
	}

	return 0;
}
