#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<int> par(n), max_dep(n);
  for (int i = 0; i < n; ++i) {
    for (int j; cin >> j, j != -1; )
      par[j] = i;
  }

  int ans = 0;
  for (int i = n - 1; i > 0; --i) {
    ans = max(ans, max_dep[i] + 1 + max_dep[par[i]]);
    max_dep[par[i]] = max(max_dep[par[i]], max_dep[i] + 1);
  }
  cout << ans << '\n';

  return 0;
}
