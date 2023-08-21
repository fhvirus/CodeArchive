#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int s, n;
	string name;

	while (cin >> s and s != 0) {
		map<string, int> name_to_id;
		vector<vector<int>> adj(s);
		vector<int> level(s);
		vector<int> require(s, 0);

		for (int i = 0, m; i < s; ++i) {
			cin >> name;
			name_to_id[name] = i;
			cin >> level[i];

			cin >> m;
			for (int j = 0; j < m; ++j) {
				cin >> name;
				adj[i].push_back(name_to_id[name]);
			}
		}

		cin >> n;
		for (int i = 0, l; i < n; ++i) {
			cin >> name >> l;
			require[name_to_id[name]] = l;
		}

		queue<int> q;
		for (int i = 0; i < s; ++i)
			if (require[i] != 0) q.push(i);

		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (const int& v: adj[u]) {
				if (require[v] != 0) continue;
				require[v] = 1;
				q.push(v);
			}
		}
		int ans = 0, tot = 0;
		for (int i = 0; i < s; ++i) {
			if (require[i] != 0)
				ans = max(ans, level[i] + require[i] - 1);
			tot += require[i];
		}
		ans = max(ans, tot + 1);

		if (ans > 99) cout << "IMPOSSIBLE\n";
		else cout << ans << '\n';
	}

	return 0;
}
