#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int kL = 30;

  int n;
  cin >> n;

  vector<int> basis(kL);
  for (int x, i = 0; i < n; ++i) {
    cin >> x;
    for (int l = kL - 1; l >= 0; --l)
      if (x >> l & 1) x ^= basis[l];
    if (x != 0) basis[__lg(x)] = x;
  }

  cout << (1 << (kL - ranges::count(basis, 0))) << '\n';

  return 0;
}
