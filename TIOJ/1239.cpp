#include <bits/stdc++.h>
using namespace std;

void answer(int ans) { cout << ans << endl; exit(0); }

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<vector<int>> adj(n);
  for (int u, v, i = 1; i < n; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  const auto go = [&adj](const auto& self, int u, int p, int len) -> int {
    multiset<int> s;
    for (int v : adj[u]) if (v != p) {
      int d = self(self, v, u, len) + 1;
      if (d == 0) return -1;
      if (d != len) {
        auto it = s.find(len - d);
        if (it != end(s)) s.erase(it);
        else s.insert(d);
      }
    }
    if (size(s) > 1) return -1;
    return empty(s) ? 0 : *begin(s);
  };

  int len = 1;
  for (; len * len <= (n - 1); ++len)
    if ((n - 1) % len == 0 and go(go, 0, -1, (n - 1) / len) == 0) answer((n - 1) / len);
  len -= 1;
  if (len * len == (n - 1)) len -= 1;
  for (; len > 1; --len)
    if ((n - 1) % len == 0 and go(go, 0, -1, len) == 0) answer(len);
  answer(1);

  return 0;
}
