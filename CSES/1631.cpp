#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  int64_t mxv = 0, sum = 0;
  for (int a, i = 0; i < n; ++i) {
    cin >> a;
    sum += a;
    mxv = max<int64_t>(mxv, a);
  }

  cout << max(2 * mxv, sum) << '\n';

  return 0;
}
