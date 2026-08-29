#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  vector<int16_t> x(n);
  for (auto &i : x) cin >> i;

  int m;
  cin >> m;
  vector<int16_t> y(m);
  for (auto &i : y) cin >> i;

  vector<int> stk;
  const auto put = [&](int j) {
    while (not empty(stk) and stk.back() == j + 1)
      stk.pop_back(), j += 2;
    stk.push_back(j);
  };
  for (int i = max(n, m) - 1; i >= 0; --i) {
    int a = (i < n ? x[i] : 0), b = (i < m ? y[i] : 0);
    for (int t = 0; t < a + b; ++t) {
      int j = i;
      if (j == 0 and not empty(stk) and stk.back() == 0) {
        stk.pop_back();
        j = 1;
      }
      if (empty(stk) or stk.back() > j) {
        put(j);
        continue;
      }
      x[max(0, j - 2)] += 1;
      stk.pop_back();
      put(j + 1);
    }
  }

  cout << stk[0] + 1;
  for (int i = 0, j = (int)size(stk)-1; i <= stk[0]; ++i) {
    cout << ' ' << (i == stk[j]);
    if (i == stk[j]) --j;
  }
  cout << '\n';

  return 0;
}
