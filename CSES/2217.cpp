#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int n, m; cin >> n >> m;
	vector<int> x(n+1, 0);
	vector<int> pos(n+2, 0);
	for (int i = 1; i <= n; ++i) {
		cin >> x[i];
		pos[x[i]] = i;
	}
	pos[n+1] = n+1;

	int ans = 1;
	for (int i = 1; i <= n; ++i)
		ans += (pos[i] < pos[i-1]);

	for (int a, b, i = 0; i < m; ++i) {
		cin >> a >> b;
		if (x[a] > x[b]) swap(a, b);
		for (int j: {a, b}) {
			ans -= pos[x[j]-1] > pos[x[j]];
			ans -= pos[x[j]] > pos[x[j]+1];
		}
		ans += (x[a] + 1 == x[b] and a > b);
		swap(pos[x[a]], pos[x[b]]);
		swap(x[a], x[b]);
		for (int j: {a, b}) {
			ans += pos[x[j]-1] > pos[x[j]];
			ans += pos[x[j]] > pos[x[j]+1];
		}
		ans -= (x[b] + 1 == x[a] and b > a);
		cout << ans << '\n';
	}

	return 0;
}
