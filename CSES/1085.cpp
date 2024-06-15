#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, k;
  cin >> n >> k;

  vector<int> x(n);
  for (int &i : x) cin >> i;

  int64_t ans = accumulate(begin(x), end(x), 0l);
  int mxv = *max_element(begin(x), end(x));
  for (int64_t l = 1l << 60; l > 0; l >>= 1) if (ans - l >= mxv) {
    int64_t t = ans - l, sum = 0, cnt = 1;
    for (int &i : x) {
      if (sum + i > t) {
        cnt += 1;
        sum = 0;
      }
      sum += i;
    }
    if (cnt <= k) ans = t;
  }

  cout << ans << '\n';

  return 0;
}
