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

  int n, k, e;
  cin >> n >> k >> e;

  vector<bool> bad(e + 1, false);
  for (int a, i = 0; i < n; ++i) {
    cin >> a;
    bad[a] = true;
  }

  vi s(k);
  for (int &i : s) cin >> i;
  sort(all(s), greater<>());

  vector<vi> dis(e + 1);
  vi source(e + 1, -1);
  dis[0] = vi(k, 0);
  source[0] = 0;
  rep (i, 0, e) if (source[i] != -1) {
    rep (j, 0, k) if (i + s[j] <= e and not bad[i + s[j]]) {
      dis[i][j] += 1;
      if (source[i + s[j]] == -1 or dis[i] > dis[i + s[j]]) {
        dis[i + s[j]] = dis[i];
        source[i + s[j]] = i;
      }
      dis[i][j] -= 1;
    }
  }

  if (source[e] == -1) {
    cout << -1 << '\n';
    exit(0);
  }
  
  vi p;
  for (int u = e; u != 0; u = source[u])
    p.push_back(u);

  cout << sz(p) << '\n';
  for (int i = sz(p) - 1; i >= 0; --i)
    cout << p[i] << " \n"[i == 0];

  return 0;
}
