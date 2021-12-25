#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int n; cin >> n;
	vector<int> p(n);
	for (int &i: p)
		cin >> i;

	nth_element(begin(p), begin(p) + n/2, end(p));
	
	long long ans = 0;
	for (int &i: p)
		ans += (i < p[n/2] ? p[n/2] - i : i - p[n/2]);

	cout << ans << '\n';

	return 0;
}
