#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<pair<int, int>> a;
  for (int i = 1; i < n; ++i)
    for (int j = i + 1; j <= n; ++j)
      if (gcd(i, j) == 1)
        a.emplace_back(i, j);

  int k = min(n, (int)size(a)) - 1;

  ranges::nth_element(a, begin(a) + k, [](auto u, auto v) {
      return u.first * v.second < v.first * u.second; });

  cout << size(a) << endl;
  cout << a[k].first << '/' << a[k].second << endl;

  return 0;
}
