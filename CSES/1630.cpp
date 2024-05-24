#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  int64_t d_sum = 0;
  vector<int> a(n);
  for (int d, i = 0; i < n; ++i) {
    cin >> a[i] >> d;
    d_sum += d;
  }

  sort(begin(a), end(a));

  int64_t f_sum = 0;
  for (auto i : a) {
    f_sum += i;
    d_sum -= f_sum;
  }

  cout << d_sum << '\n';

  return 0;
}
