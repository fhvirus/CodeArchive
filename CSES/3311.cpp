#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  vector<string> a(n);
  for (auto& s : a) cin >> s;

  bitset<4> has;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      has.set();
      has.reset(a[i][j] - 'A');
      if (i > 0) has.reset(a[i - 1][j] - 'A');
      if (j > 0) has.reset(a[i][j - 1] - 'A');
      a[i][j] = char('A' + has._Find_first());
    }
  }

  for (auto s : a) cout << s << '\n';

  return 0;
}
