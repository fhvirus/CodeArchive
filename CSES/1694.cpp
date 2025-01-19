#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
 
struct Flow {
  struct Edge {
    // rc: residual capacity
    // rid: 反向邊編號
    int v, rc, rid;
  };
  vector<vector<Edge>> adj;
  void add(int u, int v, int c) {
    adj[u].push_back({ v, c, sz(adj[v]) });
    adj[v].push_back({ u, 0, sz(adj[u]) - 1 });
  }
  vector<bool> vis;
  vector<int> dis;
  Flow (int n) : adj(n), vis(n), dis(n) {}
  int dfs(int u, int t, int f) {
    if (u == t or f == 0) return f;
    vis[u] = true;
    for (auto &[v, rc, rid]: adj[u]) {
      if (rc <= 0 or vis[v] or dis[v] != dis[u] + 1) continue;
      int df = dfs(v, t, min(f, rc));
      if (df <= 0) continue;
      rc -= df;
      adj[v][rid].rc += df;
      return df;
    }
    return 0;
  }
  ll flow(int s, int t) {
    ll ans = 0;
    while (true) {
      fill(all(dis), INT_MAX);
      queue<int> q;
      q.push(s);
      dis[s] = 0;
      while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto [v, rc, rid] : adj[u]) {
          if (rc <= 0 or dis[v] < INT_MAX) continue;
          dis[v] = dis[u] + 1;
          q.push(v);
        }
      }
 
      fill(all(vis), false);
      int df = dfs(s, t, INT_MAX);
      if (df <= 0) break;
      ans += df;
    }
    return ans;
  }
};
 
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
 
	int n, m;
	cin >> n >> m;
 
	Flow flow(n + 1);
	for (int a, b, c, i = 0; i < m; ++i) {
		cin >> a >> b >> c;
		flow.add(a, b, c);
	}
 
	cout << flow.flow(1, n) << '\n';
  return 0;
}
