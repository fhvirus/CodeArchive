#include <bits/stdc++.h>
using namespace std;

void solve() {
  int m, k;
  cin >> m >> k;

  vector<int> a(m);
  for (int i = m - 1; i >= 0; --i)
    cin >> a[i];

  int64_t t = accumulate(begin(a), end(a), 0l),
          mx = *ranges::max_element(a);
  for (int64_t l = 1l << __lg(t); l > 0; l /= 2) if (t - l >= mx) {
    int need = 0;
    for (int64_t sum = 0, i = 0; i < m; ++i) {
      if (sum + a[i] > t - l) need += 1, sum = 0;
      sum += a[i];
    }
    if (need + 1 <= k) t -= l;
  }

  vector can(k, vector<bool>(m, false));
  for (int64_t sum = 0, i = 0; i < m; ++i) {
    sum += a[i];
    if (sum > t) break;
    can[0][i] = true;
  }
  for (int i = 1; i < k; ++i) {
    for (int64_t lb = 0, sum = 0, last = LONG_MIN, j = 0; j < m; ++j) {
      sum += a[j];
      while (sum > t) sum -= a[lb++];
      can[i][j] = (last + 1 >= lb);
      if (can[i - 1][j]) last = j;
    }
  }

  for (int i = k - 1, j = m - 1; j >= 0; --j) {
    cout << a[j] << " \n"[j == 0];
    if (i > 0 and j > 0 and can[i - 1][j - 1]) cout << "/ ", --i;
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
