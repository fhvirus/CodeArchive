#include <bits/stdc++.h>
using namespace std;

void chmax(int &u, int v) { if (u < v) u = v; }

const int kCombo = 20, kFever = 32;

void solve() {
  int N;
  cin >> N >> ws;
  N *= 16;

  vector<int> a(N), pre(N + 1);
  { // preprocess, beware of reversing odd-length long notes!
    vector<string> fu(N);
    for (int i = 0; i < N; ++i) {
      if (i % 16 == 0) getline(cin, fu[i]);
      getline(cin, fu[i]);
    }
    vector<int> last(6, 0);
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < 6; ++j)
        if (fu[N - 1 - i][j] == '#') {
          last[j] ^= 1;
          a[i] += last[j];
        } else {
          last[j] = false;
          a[i] += (fu[N - 1 - i][j] == '_');
        }
    }
    partial_sum(begin(a), end(a), begin(pre) + 1);
  }

  const int L = 1 + pre[N] / 20; // max fever level
  vector dp(N, vector(L, INT_MIN));
  vector<int> upd(N, INT_MIN);
  int source = INT_MIN;
  dp[0][0] = 0;
  for (int i = 0, j = 0, sum = 0; i < N; ++i) {
    chmax(source, upd[i]);
    if (source != INT_MIN)
      chmax(dp[i][1], source + pre[i]);

    if (i > 0) sum -= a[i - 1];
    while (j < N and sum < 20) sum += a[j++];
    if (j >= N) continue;

    if (j < i + kFever) { // level up
      for (int l = 0; l + 1 < L; ++l) if (dp[i][l] != INT_MIN)
        for (int k = j, s = sum; k < i + kFever and k < N; s += a[k++])
          chmax(dp[k][l + 1], dp[i][l] + s * (l + 1));
    }
    // back to level 1, might be optimal!
    for (int l = 0; l < L; ++l) if (dp[i][l] != INT_MIN and i + kFever < N) {
      int in = pre[i + kFever] - pre[i];
      chmax(upd[j], dp[i][l] + in * l - pre[i]);
    }
  }

  int ans = pre[N];
  for (int i = max(0, N - 32); i < N; ++i) {
    for (int l = 0; l < L; ++l) if (dp[i][l] != INT_MIN) {
      int j = min(i + kFever, N);
      chmax(ans, dp[i][l] + (pre[j] - pre[i]) * l + pre[N] - pre[i]);
    }
  }
  cout << "You can get maxinum combo " << ans << ".\n";
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int M;
  cin >> M;
  while (M --> 0) solve();

  return 0;
}
