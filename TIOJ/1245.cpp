#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int kN = 128;

  for (int N; cin >> N, N != 0; ) {
    vector<vector<int>> adj(kN);
    for (int i = 1; i < N; ++i) {
      char a, b;
      cin >> a >> b;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }

    vector<int> dep(kN), par(kN), siz(kN);
    const auto dfs = [&](const auto& self, int u) -> void {
      siz[u] = 1;
      for (int v : adj[u]) if (v != par[u]) {
        dep[v] = dep[u] + 1, par[v] = u;
        self(self, v);
        siz[u] += siz[v];
      }
    };
    const auto find_deepest = [&](int root) {
      par[root] = -1;
      dfs(dfs, root);
      return (int)(ranges::max_element(dep) - begin(dep));
    };

    int root = find_deepest('A');
    int oth = find_deepest(root);

    int len = 0;
    vector<int> on(kN);
    for (int u = oth; u != -1; u = par[u]) on[u] = true, len += 1;
    cout << len << '\n';

    map<int, int> cnt;
    for (int i = 0; i < kN; ++i)
      if (not on[i] and on[par[i]])
        cnt[siz[i]] += 1;

    if (empty(cnt)) cout << "No functional group\n";
    else for (auto [v, c] : cnt) cout << 'C' << v << ':' << c << '\n';
  }

  return 0;
}
