#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  int ans = 0;
  vector<int> last(m, -1), a(m);
  for (int i = 0; i < n; ++i) {
    string s; cin >> s;
    for (int j = 0; j < m; ++j) {
      if (s[j] == '0') last[j] = i;
      a[j] = i - last[j];
    }
    ranges::sort(a, greater());
    for (int j = 0; j < m and a[j] != 0; ++j)
      ans = max(ans, (j + 1) * a[j]);
  }

  cout << ans << '\n';

  return 0;
}
