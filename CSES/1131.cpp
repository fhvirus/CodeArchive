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

  function<pii(int)> bfs = [&](int s) {
    vi dis(n + 1, -1), q;
    dis[s] = 0, q.push_back(s);
    rep (i, 0, sz(q)) {
      int u = q[i];
      for (int v : adj[u]) if (dis[v] == -1)
        dis[v] = dis[u] + 1, q.push_back(v);
    }
    auto it = max_element(all(dis));
    return pii(int(it - begin(dis)), *it);
  };

  cout << bfs(bfs(1).first).second << '\n';
}
