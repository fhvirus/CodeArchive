#include<bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector<int> w(n + 1);
	for (int i = 1; i <= n; ++i)
		cin >> w[i];
	
	vector<vector<int>> p(m);
	for (int k, i = 0; i < m; ++i) {
		cin >> k;
		p[i].resize(k);
		for (int j = 0; j < k; ++j)
			cin >> p[i][j];
		sort(begin(p[i]), end(p[i]), [&](int u, int v) { return w[u] > w[v]; });
	}

	vector<int64_t> sum_w(m, 0);
	typedef pair<int64_t, int> pii;
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	for (int i = 0; i < m; ++i)
		pq.emplace(sum_w[i], i);

	vector<int> ans(n, 0);
	for (int i = 0; i < n; ++i) {
		const auto [s, u] = pq.top(); pq.pop();
		if (p[u].empty()) {
			cout << -1 << '\n';
			exit(0);
		}
		sum_w[u] += w[p[u].back()];
		ans[i] = p[u].back();
		p[u].pop_back();
		pq.emplace(sum_w[u], u);
	}

	for (int i = 0; i < n; ++i)
		cout << ans[i] << " \n"[i == n - 1];

	return 0;
}
