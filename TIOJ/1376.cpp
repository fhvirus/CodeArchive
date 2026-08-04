#include <bits/stdc++.h>
using namespace std;

bool dfs(int j, auto& g, auto& btoa, auto& vis) {
	if (btoa[j] == -1) return 1;
	vis[j] = 1; int di = btoa[j];
	for (int e : g[di])
		if (not vis[e] and dfs(e, g, btoa, vis))
      return btoa[e] = di, true;
	return false;
}
int dfsMatching(auto& g) {
  int ans = 0;
  vector<int> btoa(size(g), -1);
	for (int i = 0; i < (int)size(g); ++i) {
    vector<bool> vis(size(btoa), 0);
		for (int j : g[i])
			if (dfs(j, g, btoa, vis)) {
				btoa[j] = i;
        ans += 1;
				break;
			}
	}
	return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  vector g(n, vector<int>());
  for (int x, y, i = 0; i < m; ++i) {
    cin >> x >> y;
    g[x].push_back(y);
  }

  cout << dfsMatching(g) << '\n';

  return 0;
}
