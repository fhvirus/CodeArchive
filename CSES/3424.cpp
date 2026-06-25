#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  if (n <= 3) { cout << "IMPOSSIBLE\n"; return 0; }
  if (n == 4) { cout << "2 2 2 2\n1 1 3 1\n1 3 4 4\n3 3 4 4\n"; return 0; }

  vector a(n, vector<int>(n));
  for (int i = 0; i < n; ++i) a[0][i] = n - i;
  for (int i = 1; i < n; ++i) ranges::fill(a[i], i + 1);
  for (int i = 0; i < n; ++i) a[i][n - 1] = 1;

  if (n % 2 == 1) {
    int d = (n + 3) / 2 - 1;
    swap(a[d][(n - 1) / 2], a[d][n - 1]);
  } else {
    int d = (n + 2) / 2 - 1;
    swap(a[d][0], a[d - 1][0]);
    swap(a[d + 1][0], a[d + 2][0]);
  }

  for (const auto& i : a)
    for (int j = 0; j < n; ++j)
      cout << i[j] << " \n"[j == n - 1];

  return 0;
}
