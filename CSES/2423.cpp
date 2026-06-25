#include <bits/stdc++.h>
using namespace std;

const vector<string> femnio = {
  "ZZYYZZYZZ",
  "ZXXYZXYYZ",
  "YYXWWXXWW",
  "XYZWYYZYW",
  "XXZZYZZYY",
};
void pave(vector<string>& a, int u, int d, int l, int r, int dir, char c) {
  for (int i = u, p = 0; i < d; i += 3 - dir, p ^= 2) {
    for (int j = l, pp = p; j < r; j += 2 + dir, pp ^= 2) {
      a[i][j] = a[i][j + 1] = a[i + 1][j] = char(c + pp);
      a[i + 2 - dir][j + dir] = a[i + 2 - dir][j + 1 + dir] =
        a[i + 1 - dir][j + 1 + dir] = char(c + pp + 1);
    }
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);


  int t;
  cin >> t;

  while (t --> 0) {
    int n, m;
    cin >> n >> m;

    bool flip = false;
    if (n % 3 != 0 or m == 3) swap(n, m), flip = true;
    if (n % 3 != 0 or m < 2 or (n == 3 and m % 2 != 0)) {
      cout << "NO\n";
      continue;
    }
    cout << "YES\n";

    vector a(n, string(m, ' '));
    if (n % 2 != 0 and m % 2 != 0) {
      for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 5; ++j)
          a[n - 9 + i][j] = femnio[j][i];
      pave(a, n - 9, n, 5, m, 0, 'I');
      n -= 9;
    }
    if (m % 2 != 0) {
      pave(a, 0, n, m - 3, m, 1, 'E');
      m -= 3;
    }
    pave(a, 0, n, 0, m, 0, 'A');

    n = int(size(a)), m = int(size(a[0]));
    if (flip) {
      for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) cout << a[i][j];
        cout << '\n';
      }
    } else for (auto i : a) cout << i << '\n';
  }

  return 0;
}
