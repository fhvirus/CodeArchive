#include <bits/stdc++.h>
using namespace std;

const int kC = 1005;
bitset<kC * kC> has, need;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  while (cin >> n) {
    for (int x, y, i = 0; i < n; ++i) {
      cin >> x >> y;
      has[x * kC + y] = true;
    }

    for (size_t p = has._Find_first(); p != has.size(); p = has._Find_next(p)) {
      bool has_l = has[p + 1] or has[p + kC + 2];
      bool has_r = has[p + kC] or has[p + 2 * kC + 1];
      if (not has_l) need[p + 1] = true;
      if (not has_r) need[p + kC] = true;
      has[p] = false;
    }

    int ans = 0;
    for (size_t p = need._Find_first(); p != need.size(); p = need._Find_next(p)) {
      ans += 1;
      need[p] = need[p + kC + 1] = false;
    }

    cout << ans << '\n';
  }

  return 0;
}
