#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string s;
  cin >> s;

  int n = 2 * int(size(s)) + 1;
  string t(n, '.');
  for (int i = 1; i < n; i += 2) t[i] = s[i / 2];

  vector<int> p(n), ans(n);
  int m = 0, r = 0;
  for (int i = 0; i < n; ++i) {
    p[i] = (r > i ? min(r - i, p[m - (i - m)]) : 1);
    while (0 <= i - p[i] and i + p[i] < n and t[i - p[i]] == t[i + p[i]]) ++p[i];
    if (i + p[i] > r) m = i, r = i + p[i];
    ans[i + p[i] - 1] = max(ans[i + p[i] - 1], p[i]);
  }

  for (int i = n - 1; i > 0; --i)
    ans[i - 1] = max(ans[i - 1], ans[i] - 1);

  for (int i = 1; i < n; i += 2)
    cout << ans[i] << " \n"[i == n - 2];

  return 0;
}
