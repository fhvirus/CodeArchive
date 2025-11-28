#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string a, b;
  cin >> a >> b;

  if (a.size() < b.size())
    a = string(b.size() - a.size(), '0') + a;

  int lcp = 0;
  while (lcp < (int) a.size() and a[lcp] == b[lcp]) ++lcp;

  int ans = (int) a.size() - lcp;
  for (int i = 0; i < lcp; ++i) ans += (a[i] == '1');

  cout << ans << '\n';

  return 0;
}
