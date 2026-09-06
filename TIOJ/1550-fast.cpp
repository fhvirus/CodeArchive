#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m >> ws;

  int ans = 0;
  vector<int> last(m, -1), nxt(m + 1), prv(m + 1);
  iota(begin(nxt), end(nxt), 1); nxt[m] = 0;
  iota(begin(prv), end(prv), -1); prv[0] = m;
  for (int i = 0; i < n; ++i) {
    string s; getline(cin, s);
    for (int j = 0; j < m; ++j) {
      if (s[j] == '0') {
        last[j] = i;
        prv[nxt[j]] = prv[j];
        nxt[prv[j]] = nxt[j];
        nxt[j] = m, prv[j] = prv[m];
        prv[nxt[j]] = j;
        nxt[prv[j]] = j;
      }
    }
    for (int j = 1, u = nxt[m]; j <= m and last[u] != i; ++j, u = nxt[u])
      ans = max(ans, j * (i - last[u]));
  }

  cout << ans << '\n';

  return 0;
}
