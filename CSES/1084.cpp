#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int n, m, k;
	cin >> n >> m >> k;

	vector<int> a(n);
	for (int &i: a) cin >> i;
	sort(begin(a), end(a));

	vector<int> b(m);
	for (int &i: b) cin >> i;
	sort(begin(b), end(b));

	int ans = 0;
	for (int i = 0, j = 0; i < n; ++i) {
		while (j < m and b[j] < a[i] - k) ++j;
		if (j == m) break;
		if (b[j] > a[i] + k) continue;
		++ans; ++j;
	}

	cout << ans << '\n';

	return 0;
}
