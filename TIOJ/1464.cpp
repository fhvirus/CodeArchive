#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  string s, t;
  cin >> s >> t;

  vector<bool> need(n + 1);

  bool a = 0;
  int ans = 0;
  for (int i = 0; i + m <= n; ++i) {
    bool f = (s[i] != t[i]);
    a ^= need[i];
    if (a ^ f) {
      a ^= 1;
      need[i + m] = 1;
      ans += 1;
    }
  }
  for (int i = n - m + 1; i < n; ++i) {
    a ^= need[i];
    if (a ^ (s[i] != t[i])) {
      cout << "No Way!!\n";
      exit(0);
    }
  }

  cout << ans << '\n';

  return 0;
}
