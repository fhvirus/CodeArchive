#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<int> t(n + 1);
  for (int i = 1; i <= n; ++i)
    cin >> t[i];

  vector<int> dep(n + 1, -1);
  const auto dfs = [&](const auto &dfs, int u) -> void {
    dep[u] = 0;
    if (dep[t[u]] == -1)
      dfs(dfs, t[u]);
    else if (dep[t[u]] == 0)
      dep[t[u]] = -2;

    if (dep[u] == -2) {
      dep[u] = dep[t[u]] + 3;
      for (int v = t[u]; v != u; v = t[v])
        dep[v] = dep[u];
    } else dep[u] = dep[t[u]] + 1;
  };
  for (int i = 1; i <= n; ++i)
    if (dep[i] == -1) dfs(dfs, i);

  for (int i = 1; i <= n; ++i)
    cout << dep[i] << " \n"[i == n];

  return 0;
}
