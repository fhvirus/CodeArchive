#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector a(n, vector<int>(n));

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      bitset<200> has;
      has.set();
      for (int k = 0; k < j; ++k) has[a[i][k]] = 0;
      for (int k = 0; k < i; ++k) has[a[k][j]] = 0;
      a[i][j] = a[j][i] = int(has._Find_first());
    }
  }

  for (auto i : a) for (int j = 0; j < n; ++j)
    cout << i[j] << " \n"[j == n - 1];

  return 0;
}
