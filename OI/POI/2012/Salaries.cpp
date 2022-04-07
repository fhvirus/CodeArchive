#include<bits/stdc++.h>
using namespace std;

struct DSU {
	vector<int> f;
	vector<bool> has;
	DSU (int n): f(n + 1), has(n + 1, 1) {
		iota(begin(f), end(f), 0);
	}
	int Find(int u) {
		return u == f[u] ? u : f[u] = Find(f[u]);
	}
	void Merge(int u, int v) {
		u = Find(u);
		v = Find(v);
		if (u != v)
			f[v] = u;
	}
	void Remove(int u) {
		Merge(u - 1, u);
		has[u] = false;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n;
	cin >> n;

	DSU dsu(n);
	vector<int> p(n + 1), z(n + 1);
	vector<vector<int>> ch(n + 1);
	int root = 0;
	vector<int> mxv(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> p[i] >> z[i];
		if (i != p[i])
			ch[p[i]].emplace_back(i);
		else {
			z[i] = n;
			root = i;
		}
		if (z[i] != 0) {
			mxv[i] = z[i];
			dsu.Remove(z[i]);
		}
	}

	queue<int> q;
	q.push(root);
	vector<vector<int>> bkt(n + 1);

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		if (z[u] != 0)
			mxv[u] = z[u];
		else
			bkt[mxv[u]].emplace_back(u);

		for (const int& v: ch[u]) {
			mxv[v] = dsu.Find(z[u] != 0 ? z[u] - 1 : mxv[u] - 1);
			q.push(v);
		}
	}

	int number_left = 0;
	int node_left = 0;

	for (int i = 1; i <= n; ++i) {
		number_left += dsu.has[i];
		node_left += bkt[i].size();

		if (number_left == 1 and bkt[i].size() == 1) {
			z[bkt[i][0]] = dsu.Find(i);
			dsu.Remove(i);
			number_left = 0;
			node_left = 0;
		}

		if (node_left == number_left) {
			number_left = 0;
			node_left = 0;
		}
	}

	for (int i = 1; i <= n; ++i)
		cout << z[i] << '\n';

	return 0;
}
