// Ref: https://github.com/mrsac7/CSES-Solutions/blob/master/src/1197%20-%20Cycle%20Finding.cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  vector<tuple<int, int, int>> es;
  for (int a, b, c, i = 0; i < m; ++i) {
    cin >> a >> b >> c;
    es.emplace_back(a, b, c);
  }

  vector<int64_t> dis(n + 1);
  vector<int> par(n + 1, -1);
  int upd = -1;
  for (int i = 0; i < n; ++i) {
    upd = -1;
    for (auto [u, v, w] : es) if (dis[v] > dis[u] + w) {
      dis[v] = dis[u] + w;
      par[v] = u;
      upd = v;
    }
  }

  if (upd == -1) {
    cout << "NO\n";
    exit(0);
  }
  cout << "YES\n";

  for (int i = 0; i < n; ++i) upd = par[upd];
  vector<int> ans;
  for (int u = par[upd]; u != upd; u = par[u])
    ans.push_back(u);
  ans.push_back(upd);
  reverse(begin(ans), end(ans));
  for (int u : ans) cout << u << ' ';
  cout << upd << '\n';

  return 0;
}
