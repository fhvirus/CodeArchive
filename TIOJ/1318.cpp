#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, T;
  cin >> n >> T;

  vector<int> one;
  vector<pair<int, int>> two;
  for (int c, h, i = 0; i < n; ++i) {
    cin >> c >> h;
    if (h <= c - h) {
      one.push_back(h);
      one.push_back(c - h);
    } else two.emplace_back(c, h);
  }

  ranges::sort(one);
  for (int i = 0; i < (int)size(one); ++i) {
    if (i > 0) one[i] += one[i - 1];
    if (one[i] > T) { one.resize(i); break; }
  }

  ranges::sort(two);
  vector<int> min_two_h(size(two) + 1, INT_MAX);
  for (int i = (int)size(two) - 1; i >= 0; --i)
    min_two_h[i] = min(min_two_h[i + 1], two[i].second);

  const auto how_many = [&](int t, int i) {
    if (t < 0) return INT_MIN;
    int o = (int) (ranges::upper_bound(one, t) - begin(one));
    int ot = (o == 0 ? 0 : one[o - 1]);
    return o + (t - ot >= min_two_h[i]);
  };

  int ans = 0, max_two_d = 0;
  for (int i = 0; i <= (int)size(two) and T + max_two_d >= 0; ++i) {
    ans = max(ans, how_many(T + max_two_d, i) + i * 2 - 1);
    ans = max(ans, how_many(T, i) + i * 2);
    if (i == (int)size(two)) break;
    T -= two[i].first;
    max_two_d = max(max_two_d, two[i].first - two[i].second);
  }

  cout << ans << '\n';

  return 0;
}
