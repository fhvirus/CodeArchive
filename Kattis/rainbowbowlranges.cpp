#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  vector<int> c;
  for (int u, i = 0; i < m; ++i) {
    cin >> u;
    if (u < n) c.push_back(n - u + 1);
  }

  sort(begin(c), end(c));
  if (not c.empty()) {
    n -= c.back();
    c.pop_back();
  }

  int ans = 1;
  for (int i : c) {
    if (i > n) break;
    ans += 1, n -= i;
  }

  cout << ans << '\n';

  return 0;
}
