#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, k;
  cin >> n >> k;

  vector<string> a(n);
  for (auto &s : a) cin >> s;

  vector<bool> ans(k);
  vector has(n, vector<int>(n));
  for (auto &s : a) {
    vector<vector<int>> pos(k);
    for (int i = 0; i < n; ++i)
      pos[s[i] - 'A'].push_back(i);
    for (int c = 0; c < k; ++c) if (not ans[c]) {
      for (int i : pos[c]) for (int j : pos[c]) {
        if (ans[c] or i <= j) break;
        if (has[i][j] >> c & 1) { ans[c] = 1; break; }
        has[i][j] |= (1 << c);
      }
    }
  }

  for (int c = 0; c < k; ++c)
    cout << (ans[c] ? "YES\n" : "NO\n");

  return 0;
}
