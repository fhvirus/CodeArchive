#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct DominatorTree {
  vi p, semi, ord, dom, f, val;
  vector<vi> adj, pre, bkt;
  void dfs(int u) {
    semi[u] = sz(ord);
    ord.push_back(u);
    for (int v : adj[u]) {
      if (semi[v] == -1) p[v] = u, dfs(v);
      pre[v].push_back(u);
    }
  }
  int eval(int u, int t = 0) {
    if (f[u] == -1) return t ? -1 : u;
    if (int p = eval(f[u], 1); p != -1) {
      if (semi[val[f[u]]] < semi[val[u]])
        val[u] = val[f[u]];
      f[u] = p;
      return t ? p : val[u];
    } return t ? f[u] : val[u];
  }
  DominatorTree(int N, const vector<vi>& adj, int r): p(N, -1), 
  semi(p), dom(p), f(p), val(N), adj(adj), pre(N), bkt(N) {
    iota(all(val), 0);
    dfs(r);
    for (int i = sz(ord); --i; ) {
      int u = ord[i];
      for (int v : pre[u])
        semi[u] = min(semi[u], semi[eval(v)]);
      bkt[ord[semi[u]]].push_back(u);
      f[u] = p[u];
      for (int v : bkt[p[u]]) {
        int w = eval(v);
        dom[v] = semi[w] < semi[v] ? w : p[u];
      }
      bkt[p[u]].clear();
    }
    dom[r] = r;
    for (int u: ord) if (dom[u] != ord[semi[u]])
      dom[u] = dom[dom[u]];
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  vector<vi> adj(n + 1);
  for (int u, v, i = 0; i < m; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
  }

  DominatorTree dt(n + 1, adj, 1);
  vi crits;
  for (int u = n; u != 1; u = dt.dom[u])
    crits.push_back(u);
  crits.push_back(1);
  sort(all(crits));

  cout << sz(crits) << '\n';
  for (int i : crits)
    cout << i << " \n"[i == n];

  return 0;
}
