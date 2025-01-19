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

  vector<vi> adj(n + 1);
  for (int u, v, i = 1; i < n; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  function<vi(int)> bfs = [&](int s) {
    vi dis(n + 1, -1), q;
    dis[s] = 0, q.push_back(s);
    rep (i, 0, sz(q)) {
      int u = q[i];
      for (int v : adj[u]) if (dis[v] == -1)
        dis[v] = dis[u] + 1, q.push_back(v);
    }
    return dis;
  };

  auto d1 = bfs(1);
  auto d2 = bfs(int(max_element(all(d1)) - begin(d1)));
  auto d3 = bfs(int(max_element(all(d2)) - begin(d2)));
  rep (i, 1, n + 1)
    cout << max(d2[i], d3[i]) << " \n"[i == n];
}
