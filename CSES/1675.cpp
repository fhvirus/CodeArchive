#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  vector<tuple<int, int, int>> es(m);
  for (auto &[c, a, b] : es)
    cin >> a >> b >> c;

  sort(begin(es), end(es));

  vector<int> f(n + 1);
  iota(begin(f), end(f), 0);

  const auto find = [&f](const auto& find, int u) -> int {
    return u == f[u] ? u : f[u] = find(find, f[u]); };

  int64_t ans = 0, cnt = n;
  for (auto [c, a, b] : es) {
    a = find(find, a);
    b = find(find, b);
    if (a == b) continue;
    f[b] = a;
    ans += c;
    cnt -= 1;
  }

  if (cnt == 1)
    cout << ans << '\n';
  else
    cout << "IMPOSSIBLE\n";

  return 0;
}
