#include <bits/stdc++.h>
using namespace std;

void gg() {
	cout << -1 << '\n';
	exit(0);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int N, M;
	cin >> N >> M;

	vector<vector<int>> adj(N + 1);
	vector<int> indeg(N + 1, 0);
	for (int u, v, i = 0; i < M; ++i) {
		cin >> u >> v;
		adj[u].emplace_back(v);
		indeg[v] += 1;
	}

	queue<int> q;
	for (int i = 1; i <= N; ++i)
		if (indeg[i] == 0) q.push(i);

	if (q.size() > 1) gg();

	vector<int> dp(N + 1, 0);
	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (const int& v: adj[u]) {
			indeg[v] -= 1;
			dp[v] = dp[u] + 1;
			if (indeg[v] == 0)
				q.push(v);
		}
	}

	auto [mni, mxi] = minmax_element(begin(dp) + 1, end(dp));
	if (*mxi != N - 1) gg();

	for (int u = mni - begin(dp), i = 1; i <= N; ++i) {
		cout << u << " \n"[i == N];
		for (const int& v: adj[u]) {
			if (dp[v] != dp[u] + 1) continue;
			u = v;
			break;
		}
	}

	return 0;
}
