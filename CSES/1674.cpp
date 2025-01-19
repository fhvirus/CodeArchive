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

  vi p(n + 1), deg(n + 1);
  rep (i, 2, n + 1) {
    cin >> p[i];
    deg[p[i]] += 1;
  }

  vi ord;
  rep (i, 1, n + 1) if (deg[i] == 0)
    ord.push_back(i);

  vi ans(n + 1);
  rep (i, 0, sz(ord)) {
    int u = ord[i], v = p[u];
    ans[v] += ans[u] + 1;
    if (--deg[v] == 0)
      ord.push_back(v);
  }
  
  rep (i, 1, n + 1)
    cout << ans[i] << " \n"[i == n];
}
