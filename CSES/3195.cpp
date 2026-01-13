#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  k = n - k;
  for (int l = 1 << __lg(max(1, k)); l > 0; l /= 2) if (k & l) {
    for (int i = 0; i + l < n; ++i)
      a[i] ^= a[i + l];
    a.resize(n -= l);
  }

  for (int i = 0; i < n; ++i)
    cout << a[i] << " \n"[i == n - 1];

  return 0;
}
