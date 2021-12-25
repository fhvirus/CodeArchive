#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int n; cin >> n;
	vector<int> pos(n+1, 0);
	for (int x, i = 1; i <= n; ++i) {
		cin >> x;
		pos[x] = i;
	}

	int ans = 1;
	for (int i = 1; i <= n; ++i)
		ans += (pos[i] < pos[i-1]);

	cout << ans << '\n';

	return 0;
}
