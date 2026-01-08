#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int mod = 1e9 + 7;

  int n;
  cin >> n;

  map<int, int> mp;
  for (int x, i = 0; i < n; ++i) {
    cin >> x;
    mp[x] += 1;
  }

  int64_t ans = 1;
  for (auto [x, c] : mp) ans = ans * (c + 1) % mod;

  cout << (ans - 1 + mod) % mod << '\n';

  return 0;
}
