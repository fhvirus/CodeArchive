#include <bits/stdc++.h>
using namespace std;

void solve() {
  int m, k;
  cin >> m >> k;

  vector<int> a(m);
  for (int &i : a) cin >> i;

  vector<bool> cut(m);
  const auto test = [&](int64_t t) {
    int need = 1;
    for (int64_t sum = 0, i = m - 1; i >= 0; --i) {
      if (sum + a[i] > t or k - need > i)
        need += 1, sum = a[i], cut[i] = true;
      else
        sum += a[i], cut[i] = false;
    }
    return need <= k;
  };

  int64_t t = accumulate(begin(a), end(a), 0l),
          mx = *ranges::max_element(a);
  for (int64_t l = 1l << __lg(t); l > 0; l /= 2)
    if (t - l >= mx and test(t - l)) t -= l;

  test(t);

  for (int i = 0; i < m; ++i) {
    cout << a[i] << " \n"[i == m - 1];
    if (cut[i]) cout << "/ ";
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while (T --> 0) solve();

  return 0;
}
