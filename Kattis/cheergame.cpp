#include <bits/stdc++.h>
using namespace std;

struct Score {
  int A, B;
  Score (int a = 0, int b = INT_MAX / 2) : A(a), B(b) {}
  bool operator < (const Score& o) const
  { return make_pair(A - B, A) < make_pair(o.A - o.B, o.A); }
  Score update(int v) const
  { return v == 1 ? Score(A + 1, B) : Score(A, B + 1); }
};

template <typename T>
void chmax(T &a, T b) { if (a < b) a = b; }

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, t, m;
  cin >> n >> t >> m;

  array<int, 91> spoil = {0};
  for (int a, b, i = 0; i < m; ++i) {
    cin >> a >> b;
    spoil[a] += 1;
    spoil[b] -= 1;
  }
  partial_sum(begin(spoil), end(spoil), begin(spoil));

  int e = n * t;
  vector<array<Score, 9>> sc(e + 1), dp(e + 1);
  sc[e][0] = Score(0, 0);

  for (int i = 0; i < 90; ++i) {
    for (int j = 0; j <= e; ++j)
      fill(begin(dp[j]), end(dp[j]), Score());

    // do nothing, -1
    for (int j = 0; j <= e; ++j) {
      for (int k = 1; k <= 4; ++k)
        chmax(dp[j][-1 + 4], sc[j][k + 4]);
      if (i == 45) {
        for (int k = -4; k <= 0; ++k)
          chmax(dp[j][-1 + 4], sc[j][k + 4]);
      } else {
        for (int k = -3; k <= 0; ++k)
          chmax(dp[j][k-1 + 4], sc[j][k + 4]);
        chmax(dp[j][0 + 4], sc[j][-4 + 4].update(-1));
      }
    }

    // break combo
    int need = spoil[i];
    if (need <= n) {
      for (int j = 0; j + need <= e; ++j) {
        for (int k = -4; k <= 4; ++k)
          chmax(dp[j][0 + 4], sc[j + need][k + 4]);
      }
    }

    // gain 1 combo
    need = spoil[i] + 1;
    if (need <= n) {
      for (int j = 0; j + need <= e; ++j) {
        for (int k = -4; k <= -1; ++k)
          chmax(dp[j][1 + 4], sc[j + need][k + 4]);
        if (i == 45) {
          for (int k = 0; k <= 4; ++k)
            chmax(dp[j][1 + 4], sc[j + need][k + 4]);
        } else {
          for (int k = 0; k <= 3; ++k)
            chmax(dp[j][k+1 + 4], sc[j + need][k + 4]);
          chmax(dp[j][0 + 4], sc[j + need][4 + 4].update(1));
        }
      }
    }

    swap(dp, sc);
  }

  Score ans(0, INT_MAX);
  for (auto &i : sc) for (auto& j : i) chmax(ans, j);

  cout << ans.A << ' ' << ans.B << '\n';

  return 0;
}
