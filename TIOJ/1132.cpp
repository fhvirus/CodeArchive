#include <bits/stdc++.h>
using namespace std;

const int kC = 1005;
bool has[kC][kC], need[kC][kC];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  while (cin >> n) {
    vector<pair<int, int>> horses(n), spots;
    for (auto &[x, y] : horses) {
      cin >> x >> y;
      has[x][y] = true;
    }
    sort(begin(horses), end(horses));

    for (auto [x, y] : horses) {
      bool has_l = has[x][y + 1] or has[x + 1][y + 2];
      bool has_r = has[x + 1][y] or has[x + 2][y + 1];
      if (not has_l) need[x][y + 1] = true, spots.emplace_back(x, y + 1);
      if (not has_r) need[x + 1][y] = true, spots.emplace_back(x + 1, y);
      has[x][y] = false;
    }
    sort(begin(spots), end(spots));

    int ans = 0;
    for (auto [x, y] : spots) if (need[x][y]) {
      ans += 1;
      need[x][y] = need[x + 1][y + 1] = false;
    }

    cout << ans << '\n';
  }

  return 0;
}
