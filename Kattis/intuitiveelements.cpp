#include <bits/stdc++.h>
using namespace std;

int get_mask(const string& s) {
  int mask = 0;
  for (char c : s) mask |= (1 << (c - 'a'));
  return mask;
}

void solve() {
  string a, b;
  cin >> a >> b;
  int ma = get_mask(a), mb = get_mask(b);
  cout << ((ma & mb) == mb ? "YES\n" : "NO\n");
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int t;
  cin >> t;

  while (t --> 0) solve();

  return 0;
}

