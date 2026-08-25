#include <bits/stdc++.h>
using namespace std;

const int delta[5] { 0, 1, 0, -1, 0 };

void solve() {
  int R, C;
  string s;
  cin >> R >> C; cin.ignore();
  getline(cin, s);

  string ans(R * C, ' ');

  int i = 0, j = 0, dir = 0;
  for (char c : s) {
    int v = (c == ' ' ? 0 : c - 'A' + 1);
    for (int t = 4; t >= 0; --t) {
      ans[i * C + j] = char('0' + (v >> t & 1));

      int ni = i + delta[dir], nj = j + delta[dir + 1];
      if (0 > min(ni, nj) or ni >= R or nj >= C or
          ans[ni * C + nj] != ' ') dir = (dir + 1) % 4;
      i += delta[dir], j += delta[dir + 1];
    }
  }
  for (char &c : ans) if (c == ' ') c = '0';

  cout << ans << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int k;
  cin >> k;
  for (int i = 1; i <= k; ++i) {
    cout << i << ' ';
    solve();
  }

  return 0;
}

