#include <bits/stdc++.h>
using namespace std;

constexpr int pow3(int n) {
  int r = 1;
  while (n --> 0) r *= 3;
  return r;
}

constexpr int kM = 10;
constexpr int kS2 = 1 << ((kM - 1) * 2), kS3 = pow3(kM - 1);
int t23[kS2], t32[kS3];

int get_d(int v, int j) { return v >> (j * 2) & 0b11; }
int set_d(int v, int j, int d) { return (v & ~(0b11 << (j * 2))) | (d << (j * 2)); }

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<int> g(n);
  for (int x, y, i = 0; i < k; ++i) {
    cin >> x >> y;
    g[x - 1] |= (1 << (y - 1));
  }

  if (m == 1) {
    cout << 0 << '\n';
    return;
  }

  const int s = pow3(m - 1);
  vector<int> sc(s * 2, INT_MIN), dp(s * 2);
  sc[0 * 2 + 0] = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 1; j < m; ++j) {
      ranges::fill(dp, INT_MIN);

      for (int a = 0; a < s; ++a) for (int l : {0, 1}) {
        int val = sc[a * 2 + l];
        if (val == INT_MIN) continue;
        const int state = t32[a];

        if (g[i] >> (j - 1) & 0b11) {
          int to = set_d(state, j - 1, 0);
          to = t23[to] * 2 + 0;
          dp[to] = max(dp[to], val);
        } else {
          int d = l ? 0 : 1 + get_d(state, j - 1);
          int pd = j > 1 ? get_d(state, j - 2) : 0;
          // do nothing
          int to = set_d(state, j - 1, min(d, 2));
          to = t23[to] * 2 + 0;
          dp[to] = max(dp[to], val);
          // put horizontal
          if (d >= 3) {
            to = set_d(state, j - 1, 0);
            if (j > 1) to = set_d(to, j - 2, 0);
            if (j + 1 < m) to = set_d(to, j, 0);
            to = t23[to] * 2 + (j != m - 1);
            dp[to] = max(dp[to], val + 1);
          }
          // put vertical
          if (d >= 2 and pd >= 2) {
            to = set_d(state, j - 1, 0);
            to = set_d(to, j - 2, 0);
            if (j > 2) to = set_d(to, j - 3, 0);
            if (j + 1 < m) to = set_d(to, j, 0);
            to = t23[to] * 2 + (j != m - 1);
            dp[to] = max(dp[to], val + 1);
          }
        }
      }

      swap(dp, sc);
    }
  }

  cout << *ranges::max_element(sc) << '\n';
  return;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (int i = 0; i < kS3; ++i) {
    int v = 0;
    for (int t = i, j = 0; j < kM - 1; ++j) {
      v = set_d(v, j, t % 3);
      t /= 3;
    }
    t23[v] = i, t32[i] = v;
  }

  int T;
  cin >> T;
  while (T --> 0) solve();

  return 0;
}
