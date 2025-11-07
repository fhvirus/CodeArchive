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

  int n, m;
  cin >> n >> m;

  vi h(m, 0);
  int ans = 0;
  rep (i, 0, n) {
    string s;
    cin >> s;
    rep (j, 0, m) h[j] = (s[j] == '*' ? 0 : h[j] + 1);
    vector<pii> stk;
    stk.emplace_back(-1, 0);
    rep (j, 0, m) {
      while (stk.back().second > h[j]) {
        ans = max(ans, stk.back().second * (j - end(stk)[-2].first - 1));
        stk.pop_back();
      }
      stk.emplace_back(j, h[j]);
    }
    rep (j, 1, sz(stk))
      ans = max(ans, stk[j].second * (m - stk[j - 1].first - 1));
  }

  cout << ans << '\n';

  return 0;
}
