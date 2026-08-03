#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  int ans = 0;
  vector<int> pos(n + 1, -1);
  array<int, 2> rb({-1, -1});
  for (int a, i = 0; i < 2 * n; ++i) {
    cin >> a;
    if (pos[a] == -1) pos[a] = i;
    else {
      if (rb[0] < rb[1]) swap(rb[0], rb[1]);
      for (int j : {0, 1}) if (rb[j] < pos[a]) {
        rb[j] = i;
        ans += 1;
        break;
      }
    }
  }
  cout << ans << '\n';

  return 0;
}
