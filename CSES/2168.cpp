#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<tuple<int, int, int>> a;
  for (int x, y, i = 0; i < n; ++i) {
    cin >> x >> y;
    a.emplace_back(x, -y, i);
  }

  sort(begin(a), end(a));

  vector<bool> in(n), out(n);

  int pre_y_max = -1;
  for (auto [x, y, i] : a) {
    y = -y;
    in[i] = (pre_y_max >= y);
    pre_y_max = max(pre_y_max, y);
  }

  int suf_y_min = 1e9 + 8e7;
  reverse(begin(a), end(a));
  for (auto [x, y, i] : a) {
    y = -y;
    out[i] = (suf_y_min <= y);
    suf_y_min = min(suf_y_min, y);
  }

  for (int i = 0; i < n; ++i)
    cout << out[i] << " \n"[i + 1 == n];
  for (int i = 0; i < n; ++i)
    cout << in[i] << " \n"[i + 1 == n];

  return 0;
}
