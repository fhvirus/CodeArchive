#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

bool dfs(int a, int L, vector<vi>& g, vi& btoa, vi& A, vi& B) {
  if (A[a] != L) return 0;
  A[a] = -1;
  for (int b : g[a]) if (B[b] == L + 1) {
    B[b] = 0;
    if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
      return btoa[b] = a, 1;
  }
  return 0;
}
int hopcroftKarp(vector<vi>& g, vi& btoa) {
  int res = 0;
  vi A(g.size()), B(btoa.size()), cur, next;
  for (;;) {
    fill(all(A), 0);
    fill(all(B), 0);
    cur.clear();
    for (int a : btoa) if(a != -1) A[a] = -1;
    rep(a,0,sz(g)) if(A[a] == 0) cur.push_back(a);
    for (int lay = 1;; lay++) {
      bool islast = 0;
      next.clear();
      for (int a : cur) for (int b : g[a]) {
        if (btoa[b] == -1) {
          B[b] = lay;
          islast = 1;
        }
        else if (btoa[b] != a && !B[b]) {
          B[b] = lay;
          next.push_back(btoa[b]);
        }
      }
      if (islast) break;
      if (next.empty()) return res;
      for (int a : next) A[a] = lay;
      cur.swap(next);
    }
    rep(a,0,sz(g))
      res += dfs(a, 0, g, btoa, A, B);
  }
}

vi find_min_cover(vector<vi>& adj) {
  vi btoa(1000, -1);
  int num = hopcroftKarp(adj, btoa);
  vi vis(2000), q;
  for (int a : btoa) if (a != -1) vis[a] = 1;
  rep (i, 0, 1000) if (vis[i] == 0) q.push_back(i);
  rep (i, 0, 1000) vis[i] = 1;
  rep (i, 0, sz(q)) {
    int u = q[i];
    vis[u] = 0;
    for (int v : adj[u]) {
      vis[v + 1000] = 1;
      if (btoa[v] != -1 and vis[btoa[v]])
        q.push_back(btoa[v]);
    }
  }
  q.clear();
  rep (i, 0, 2000) if (vis[i]) q.push_back(i + 1000);
  assert(sz(q) == num);
  return q;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int m;
  cin >> m;

  vector<vi> adj(1000);
  for (int u, v, i = 0; i < m; ++i) {
    cin >> u >> v;
    adj[u - 1000].push_back(v - 2000);
  }

  auto ans = find_min_cover(adj);
  adj[9].clear();
  auto with_9 = find_min_cover(adj);
  if (sz(ans) == sz(with_9) + 1) {
    ans = with_9;
    ans.push_back(1009);
  }

  cout << sz(ans) << '\n';
  for (int i : ans) cout << i << '\n';

  return 0;
}
