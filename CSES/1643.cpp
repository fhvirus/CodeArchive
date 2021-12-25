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

	long long ans = -1e18, sum = -1e18;
	for (int &i: x) {
		sum = max((long long) i, sum + i);
		ans = max(ans, sum);
	}

	cout << ans << '\n';

	return 0;
}
