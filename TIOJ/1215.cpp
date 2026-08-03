#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  vector<int> height = {1, 3};
  while (size(height) < 7)
    height.push_back(height.back() * 2);

  for (int n; cin >> n, n != 0; ) {
    int l = __lg(n), h = height[l];
    vector g(h, string(h * 2 - 1, ' '));
    queue<array<int, 4>> q;
    q.push({ 0, 0, 1, l });
    while (not empty(q)) {
      auto [x, y, id, l] = q.front(); q.pop();
      int h = height[l], len = (l > 0 ? h - height[l - 1] - 1 : 0);
      g[x][y + h - 1] = '*';
      if (id * 2 <= n) {
        for (int i = 1; i <= len; ++i)
          g[x + i][y + h - 1 - i] = '/';
        q.push({ x + len + 1, y, id * 2, l - 1 });
      }
      if (id * 2 + 1 <= n) {
        for (int i = 1; i <= len; ++i)
          g[x + i][y + h - 1 + i] = '\\';
        q.push({ x + len + 1, y + h + (l == 1), id * 2 + 1, l - 1 });
      }
    }
    for (auto &s : g) {
      while (s.back() == ' ') s.pop_back();
      cout << s << '\n';
    }
  }

  return 0;
}
