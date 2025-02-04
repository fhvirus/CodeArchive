#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct MinCostFlow {
  struct E { int v, c; ll k; int r, rc; };
  vector<vector<E>> adj;
  vector<int> par, par_eid;
  MinCostFlow(int n): adj(n), par(n), par_eid(n) {}
  void add(int u, int v, int c, ll k) {
    adj[u].push_back({v, c, k, (int) adj[v].size(), c});
    adj[v].push_back({u, 0, -k, (int) adj[u].size() - 1, 0});
  }
  ll spfa(int s, int t) {
    fill(begin(par), end(par), -1);
    vector<ll> dis(par.size(), LLONG_MAX);
    vector<bool> in_q(par.size(), false);
    queue<int> q;
    dis[s] = 0; q.push(s); in_q[s] = true;
    while (!q.empty()) {
      int u = q.front(); q.pop(); in_q[u] = false;
      for (int i = 0; i < (int) adj[u].size(); ++i) {
        auto &[v, c, k, r, rc] = adj[u][i];
        if (rc > 0 and dis[u] + k < dis[v]) {
          dis[v] = dis[u] + k;
          par[v] = u;
          par_eid[v] = i;
          if (!in_q[v]) q.push(v);
          in_q[v] = true;
        }
      }
    }
    return dis[t];
  }
  pair<int, ll> flow(int s, int t) {
    int flow = 0;
    ll cost = 0, d;
    while ((d = spfa(s, t)) < LLONG_MAX) {
      int cur = INT_MAX;
      for (int u = t; u != s; u = par[u]) 
        cur = min(cur, adj[par[u]][par_eid[u]].rc);
      flow += cur, cost += d * cur;
      for (int u = t; u != s; u = par[u]) {
        cur = min(cur, adj[par[u]][par_eid[u]].rc);
        adj[par[u]][par_eid[u]].rc -= cur;
        adj[u][ adj[par[u]][par_eid[u]].r ].rc += cur;
      }
    }
    return make_pair(flow, cost);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  MinCostFlow mcf(1 + n + n + 1);
  rep (i, 1, n + 1) rep (j, 1, n + 1) {
    int c;
    cin >> c;
    mcf.add(i, n + j, 1, c);
  }

  rep (i, 1, n + 1) mcf.add(0, i, 1, 0);
  rep (i, 1, n + 1) mcf.add(n + i, 1 + n + n, 1, 0);

  auto [flow, cost] = mcf.flow(0, 1 + n + n);
  cout << cost << '\n';

  rep (i, 1, n + 1) {
    for (auto E : mcf.adj[i])
      if (E.c - E.rc == 1) {
        cout << i << ' ' << E.v - n << '\n';
        break;
      }
  }

  return 0;
}
