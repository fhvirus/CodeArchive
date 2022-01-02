#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n; cin >> n;
	vector<int> k(n);
	for (int &i: k) cin >> i;

	vector<int> lis;
	for (int &i: k) {
		int p = upper_bound(begin(lis), end(lis), i) - begin(lis);
		if (p == lis.size()) lis.emplace_back(i);
		else lis[p] = i;
	}

	cout << (int) lis.size() << '\n';
	return 0;
}
