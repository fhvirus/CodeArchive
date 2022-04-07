#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int x, n;
	cin >> x >> n;

	vector<pair<int, int>> cut(n + 2);
	vector<int> pos(n + 2);

	for (int i = 1; i <= n; ++i) {
		cin >> pos[i];
		cut[i] = pair<int, int>(pos[i], i);
	}
	pos[0] = 0;
	cut[0] = pair<int, int>(0, 0);
	pos[n + 1] = x;
	cut[n + 1] = pair<int, int>(x, n + 1);
	sort(begin(cut), end(cut));

	vector<int> nxt(n + 2), prv(n + 2);
	vector<int> ans(n + 1, 0);
	for (int i = 1; i <= n; ++i) {
		nxt[cut[i].second] = cut[i + 1].second;
		prv[cut[i].second] = cut[i - 1].second;
		ans[n] = max(ans[n], cut[i + 1].first - cut[i].first);
		ans[n] = max(ans[n], cut[i].first - cut[i - 1].first);
	}

	for (int i = n; i >= 1; --i) {
		ans[i - 1] = max(ans[i - 1], pos[nxt[i]] - pos[prv[i]]);
		ans[i - 1] = max(ans[i - 1], ans[i]);
		nxt[prv[i]] = nxt[i];
		prv[nxt[i]] = prv[i];
	}

	for (int i = 1; i <= n; ++i)
		cout << ans[i] << " \n"[i == n];

	return 0;
}
