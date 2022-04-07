#include <bits/stdc++.h>
using namespace std;

const int kN = 1000001;
int N, f[kN], deg[kN];
bitset<kN> vis;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 1; i <= N; ++i) {
		cin >> f[i];
		deg[f[i]] += 1;
	}

	queue<int> q;
	for (int i = 1; i <= N; ++i)
		if (deg[i] == 0) q.push(i);

	while (!q.empty()) {
		int u = q.front(); q.pop();
		vis[u] = 1;
		if ((deg[f[u]] -= 1) == 0)
			q.push(f[u]);
	}

	int ans = 0;
	for (int i = 1; i <= N; ++i) {
		if (vis[i]) continue;
		ans += 1;
		for (int u = i; !vis[u]; u = f[u])
			vis[u] = true;
	}

	cout << ans << '\n';

	return 0;
}
