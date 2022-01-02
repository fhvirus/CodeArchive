#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, x; cin >> n >> x;
	vector<pair<int, int>> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i].first;
		a[i].second = i + 1;
	}

	sort(begin(a), end(a));

	for (int i = 0; i < n; ++i) {
		int j = lower_bound(begin(a) + i + 1, end(a), pair<int, int>(x - a[i].first, 0)) - begin(a);
		if (j == n or a[i].first + a[j].first != x) continue;
		cout << a[i].second << ' ' << a[j].second << '\n';
		return 0;
	}

	cout << "IMPOSSIBLE\n";

	return 0;
}
