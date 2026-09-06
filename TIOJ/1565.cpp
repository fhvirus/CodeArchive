#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (int N, H; cin >> N >> H; ) {
    vector<int> a(N);
    for (int &i : a) cin >> i;
    for (int i = 0; i < N; ++i)
      for (int j = i + 1; j < N; ++j)
        a.push_back(a[i] + a[j]);
    ranges::sort(a); a.erase(ranges::unique(a).begin(), end(a));

    for (int b, i = 0; i < H; ++i) {
      cin >> b;
      int p = (int) (ranges::lower_bound(a, b) - begin(a));
      int prv = (p > 0 ? a[p - 1] : INT_MIN / 2),
          nxt = (p < (int)size(a) ? a[p] : INT_MAX / 2);
      cout << (abs(b - prv) <= abs(b - nxt) ? prv : nxt) << '\n';
    }
    cout << '\n';
  }

  return 0;
}
