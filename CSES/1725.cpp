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

  int n, a, b;
  cin >> n >> a >> b;

  vector<double> sc(1, 1);
  for (int i = 1; i <= n; ++i) {
    vector<double> dp(sz(sc) + 6, 0);
    for (int j = 1; j < sz(dp); ++j) {
      for (int k = max(j - 6, 0); k < j and k < sz(sc); ++k)
        dp[j] += sc[k] / 6;
    }
    swap(dp, sc);
  }

  double ans = accumulate(begin(sc) + a, begin(sc) + b + 1, 0.0);
  cout << setprecision(6) << fixed << roundeven(1e6 * ans) / 1e6 << '\n';
}
