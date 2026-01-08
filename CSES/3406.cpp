// Fermat polygonal number theorem where n = 3
#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int t;
  cin >> t;

  int64_t cur = 2, sum = 0;
  vector<int64_t> tri(1, 1);

  while (t --> 0) {
    int64_t n;
    cin >> n;

    for (; tri.back() < n; ++cur) {
      tri.push_back(cur * (cur + 1) / 2);
      sum += tri.back();
    }

    int p = int(ranges::lower_bound(tri, n) - begin(tri));
    int ans = (tri[p] == n ? 1 : 3);
    if (ans == 3) {
      for (int r = p - 1, l = 0; l <= r; --r) {
        while (l <= r and tri[l] + tri[r] < n) ++l;
        if (tri[l] + tri[r] == n) {
          ans = 2;
          break;
        }
      }
    }

    cout << ans << '\n';
  }

  return 0;
}
