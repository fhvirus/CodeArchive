#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int di[4] = { 1, 0, -1, 0 };
  const int dj[4] = { 0, 1, 0, -1 };
  const auto ok = [&](int i, int j) { return 0 <= i and i < 8 and 0 <= j and j < 8; };

  int k;
  cin >> k;

  vector<vector<double>> p(8, vector<double>(8, 1));
  rep (a, 0, 8) rep (b, 0, 8) {
    vector<vector<double>> sc(8, vector<double>(8, 0));
    sc[a][b] = 1;
    rep (n, 0, k) {
      vector<vector<double>> dp(8, vector<double>(8, 0));
      rep (i, 0, 8) rep (j, 0, 8) {
        int cnt = 0;
        rep (d, 0, 4) cnt += ok(i + di[d], j + dj[d]);
        rep (d, 0, 4) if(ok(i + di[d], j + dj[d]))
          dp[i + di[d]][j + dj[d]] += sc[i][j] / cnt;
      }
      swap(dp, sc);
    }
    rep (i, 0, 8) rep (j, 0, 8)
      p[i][j] *= (1 - sc[i][j]);
  }
  double ans = 0;
  rep (i, 0, 8) rep (j, 0, 8) ans += p[i][j];
  cout << setprecision(6) << fixed << roundeven(ans * 1e6) / 1e6 << '\n';
}
