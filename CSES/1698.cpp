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

  int n;
  cin >> n;

  vi a(n + 1);
  rep (i, 1, n + 1) cin >> a[i];

  vector<vector<pii>> sol(2);
  const auto op = [&](int r, int u, int v) {
    sol[r].emplace_back(u, v);
    swap(a[u], a[v]);
  };
  for (int i = 1; i <= n; ++i) if (a[i] != i) {
    vi p;
    for (int u = i; u != i or p.empty(); u = a[u])
      p.push_back(u);
    if (sz(p) == 2) op(0, p[0], p[1]);
    else {
      rep (r, 0, 2) for (int u = r, v = sz(p) - 1; u < v; ++u, --v)
        op(r, p[u], p[v]);
    }
  }

  while (not sol.empty() and sol.back().empty()) sol.pop_back();
  cout << sz(sol) << '\n';
  for (const auto &s : sol) {
    cout << sz(s) << '\n';
    for (auto [u, v] : s)
      cout << u << ' ' << v << '\n';
  }

  return 0;
}
