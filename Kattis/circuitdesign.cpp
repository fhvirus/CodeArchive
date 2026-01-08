#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<vector<int>> adj(n + 1);
  for (int a, b, i = 1; i < n; ++i) {
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  vector<int> siz(n + 1), ord(1, 1), par(n + 1);
  for (int i = 0; i < n; ++i) {
    int u = ord[i];
    siz[u] = 1;
    for (int v : adj[u]) if (siz[v] == 0) {
      par[v] = u;
      ord.push_back(v);
    }
  }
  for (int u : ord | views::reverse)
    siz[par[u]] += siz[u];

  vector<pair<double, double>> pos(n + 1), deg(n + 1);
  deg[1] = make_pair(.0, 2 * M_PI);
  for (int u : ord) if (siz[u] > 1) {
    auto [lb, rb] = deg[u];
    double d = (rb - lb) / (siz[u] - 1);
    for (int v : adj[u]) if (v != par[u]) {
      double vb = lb + d * siz[v];
      double vd = (lb + vb) / 2;
      pos[v] = make_pair(pos[u].first + sin(vd), pos[u].second + cos(vd));
      deg[v] = make_pair(lb, vb);
      lb = vb;
    }
  }

  cout << setprecision(7) << fixed;
  for (int i = 1; i <= n; ++i)
    cout << pos[i].first << ' ' << pos[i].second << '\n';

  return 0;
}
