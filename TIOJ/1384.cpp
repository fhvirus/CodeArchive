#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<pair<int, int>> a(n);
  for (auto &[T, H] : a) cin >> T >> H;
  
  ranges::sort(a);
  vector<int> dp;

  for (auto [_, v] : a) {
    auto it = ranges::upper_bound(dp, v);
    if (it == end(dp)) dp.push_back(v);
    else *it = v;
  }

  cout << n - (int)size(dp) << '\n';

  return 0;
}
