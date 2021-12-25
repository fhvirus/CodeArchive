#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
using namespace std;
typedef pair<int, int> pii;

const int kN = 100001;
const int kM = 200002;
int n, m;
vector<pii> adj[kN];
int in[kN];
long long dis[kN];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int u, v, w, i = 1; i <= m; ++i) {
		cin >> u >> v >> w;
		adj[u].emplace_back(v, w);
		++in[v];
	}

	for (int i = 2; i <= n; ++i)
		dis[i] = 1e18;

	queue<int> q;
	q.push(1);

	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (auto &[v, w]: adj[u]) {
			dis[v] = min(dis[v], dis[u] + w);
			if (--in[v] == 0)
				q.push(v);
		}
	}

	long long ans = 0;
	for (int i = 2; i <= n; ++i)
		ans += dis[i];
	cout << ans << '\n';

	return 0;
}
