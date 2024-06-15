#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, x;
  cin >> n >> x;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  map<int, pair<int, int>> mp;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (a[i] + a[j] >= x or mp.count(x - a[i] - a[j]) == 0) continue;
      auto [k, l] = mp[x - a[i] - a[j]];
      cout << k + 1 << ' ' << l + 1 << ' ' << i + 1 << ' ' << j + 1 << '\n';
      exit(0);
    }
    for (int j = 0; j < i; ++j)
      mp[a[i] + a[j]] = make_pair(j, i);
  }

  cout << "IMPOSSIBLE\n";


  return 0;
}
