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
  sort(all(s));

  vector<vector<pii>> dis(e + 1);
  vi source(e + 1, -1);
  source[0] = 0;
  for (int i = 0; i < e; ++i) if (source[i] != -1) {
    for (int j : s) {
      if (i + j > e) break;
      if (bad[i + j]) continue;
      auto nd = dis[i];
      for (auto it = begin(nd); ; it = next(it)) {
        if (it != end(nd) and it->first == j) {
          it->first += 1;
          break;
        } else if (it == end(nd) or it->first < j) {
          nd.insert(it, pii(j, 1));
          break;
        }
      }
      if (nd > dis[i + j]) {
        dis[i + j] = nd;
        source[i + j] = i;
      }
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
