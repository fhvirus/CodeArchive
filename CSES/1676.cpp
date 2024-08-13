#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  vector<int> f(n + 1, -1);
  const auto find = [&f](const auto& find, int u) -> int {
    return f[u] < 0 ? u : f[u] = find(find, f[u]); };

  int cnt = n, mx_size = 1;
  for (int a, b, i = 0; i < m; ++i) {
    cin >> a >> b;
    a = find(find, a);
    b = find(find, b);
    if (a != b) {
      f[a] += f[b];
      f[b] = a;
      mx_size = max(mx_size, -f[a]);
      cnt -= 1;
    }
    cout << cnt << ' ' << mx_size << '\n';
  }

  return 0;
}
