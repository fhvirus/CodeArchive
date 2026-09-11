#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
  const int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

  int n, m;
  cin >> n >> m;

  if (m == 1) { cout << "0 0\n"; exit(0); }
  m -= 1;

  int x = 0, y = (1 << (n - 1));
  for (int l = __lg(m) - 1, d = 2, t = n - 2; l >= 0; --l, --t) {
    int dir = (m >> l & 1);
    d = (dir ? (d + 7) : (d + 1)) % 8;
    x += dx[d] << t, y += dy[d] << t;
  }

  cout << x << ' ' << y << '\n';

  return 0;
}
