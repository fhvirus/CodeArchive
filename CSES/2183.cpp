#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int n; cin >> n;
	vector<int> x(n);
	for (int &i: x)
		cin >> i;

	sort(begin(x), end(x));

	long long sum = 0;
	for (int &i: x) {
		if (sum + 1 < i) break;
		sum += i;
	}

	cout << sum + 1 << '\n';

	return 0;
}
