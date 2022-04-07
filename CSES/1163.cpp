#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int x, n;
	cin >> x >> n;

	set<int> cut;
	multiset<int> len;

	cut.insert(0);
	cut.insert(x);
	len.insert(x);

	for (int p, i = 1; i <= n; ++i) {
		cin >> p;
		auto it = cut.insert(p).first;
		auto pr = prev(it);
		auto nx = next(it);
		len.erase(len.find(*nx - *pr));
		len.insert(*nx - *it);
		len.insert(*it - *pr);
		cout << *rbegin(len) << " \n"[i == n];
	}

	return 0;
}
