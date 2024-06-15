#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  vector<int> f(n + 1);
  iota(begin(f), end(f), 0);

  const auto top = [&](const auto& top, int u) -> int {
    return u == f[u] ? u : f[u] = top(top, f[u]); };

  for (int a, b, i = 0; i < m; ++i) {
    cin >> a >> b;
    a = top(top, a);
    b = top(top, b);
    if (a != b) f[a] = b;
  }

  vector<int> t;
  for (int i = 1; i <= n; ++i)
    if (i == f[i]) t.push_back(i);

  cout << t.size() - 1 << '\n';
  for (int i = 1; i < (int) t.size(); ++i)
    cout << t[0] << ' ' << t[i] << '\n';

  return 0;
}
