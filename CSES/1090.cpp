#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, x; cin >> n >> x;
	vector<int> p(n);
	for (int &i: p) cin >> i;

	sort(begin(p), end(p));
	reverse(begin(p), end(p));
	int h, t;
	for (h = 0, t = n - 1; h <= t; ++h)
		if (p[h] + p[t] <= x) --t;
	cout << h << '\n';

	return 0;
}
