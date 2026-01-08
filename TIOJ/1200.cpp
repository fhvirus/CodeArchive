#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (int a, b, c; cin >> a >> b >> c, a; ) {
    vector<string> g(max({2 * a + 2, b + 1, c + 1}), string(4 * a + b + c + 7, ' '));

    // 囧
    for (int i = 0; i < 2 * a + 2; ++i) g[i][0] = g[i][4 * a + 1] = '*';
    for (int i = 0; i < 4 * a + 2; ++i) g[0][i] = g[2 * a + 1][i] = '*';
    for (int i = 1; i <= a; ++i) g[a + i][2 * i - 1] = g[a + i][2 * i] = '*';
    for (int i = 1; i <= a; ++i) g[a + 1 + i][2 * a + 1] = '*';
    for (int i = 1; i <= 2 * a; ++i) g[a + 1][2 * a + i] = '*';
    for (int i = 1; i <= 2 * a; ++i) g[a - 1][a + i] = '*';
    for (int i = 1; i < a; ++i) g[i][a + 1] = g[i][3 * a] = '*';

    // r
    int t = 4 * a + 4;
    for (int i = 0; i <= b; ++i) g[i][t] = '*';
    for (int i = 1; i <= b; ++i) g[b - abs(2 - i)][t + i] = '*';

    // z
    t += b + 2;
    for (int i = 0; i <= c; ++i)
      g[0][t + i] = g[i][t + i] = g[c][t + i] = '*';

    for (auto s : g | views::reverse) cout << s << '\n';
    cout << '\n';
  }


  return 0;
}
