#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  a.resize(2 << __lg(max(n - 1, 1)));

  for (int n = int(size(a)), l = 1; l < n; l *= 2)
    for (int i = 0; i < n; i += 2 * l)
      for (int j = i; j < i + l; ++j)
        a[j + l] ^= a[j];

  for (int i = 0; i < n; ++i)
    cout << a[i] << " \n"[i == n - 1];

  return 0;
}
