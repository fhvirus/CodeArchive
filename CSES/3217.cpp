#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int di[8] = { 2, 2, 1, 1, -1, -1, -2, -2 };
  const int dj[8] = { 1, -1, 2, -2, 2, -2, 1, -1 };

  int n;
  cin >> n;

  vector a(n, vector<int>(n, -1));
  queue<pair<int, int>> q;
  a[0][0] = 0, q.emplace(0, 0);
  while (not q.empty()) {
    auto [i, j] = q.front(); q.pop();
    for (int d = 0; d < 8; ++d) {
      int ni = i + di[d], nj = j + dj[d];
      if (0 <= ni and ni < n and 0 <= nj and nj < n and a[ni][nj] == -1)
        a[ni][nj] = a[i][j] + 1, q.emplace(ni, nj);
    }
  }

  for (auto i : a) for (int j = 0; j < n; ++j)
    cout << i[j] << " \n"[j == n - 1];

  return 0;
}
