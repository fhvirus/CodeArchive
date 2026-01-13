#include <bits/stdc++.h>
using namespace std;

void FWHT(auto &a) {
  for (int n = int(size(a)), l = 1; l < n; l *= 2)
    for (int i = 0; i < n; i += 2 * l)
      for (int j = i; j < i + l; ++j) {
        auto &u = a[j], &v = a[j + l];
        tie(u, v) = make_pair(u + v, u - v);
      }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int kC = 1 << 20;

  int n;
  cin >> n;

  vector<int64_t> a(kC);
  int pre = 0; a[pre] = 1;
  for (int x, i = 0; i < n; ++i) {
    cin >> x;
    a[pre ^= x] = 1;
  }

  FWHT(a);
  for (auto &i : a) i *= i;
  FWHT(a);

  a[0] = a[0] / kC - (n + 1);

  cout << (kC - ranges::count(a, 0)) << '\n';
  for (int i = 0; i < kC; ++i)
    if (a[i] != 0) cout << i << ' ';
  cout << '\n';

  return 0;
}
