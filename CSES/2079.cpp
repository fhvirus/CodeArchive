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

  vi siz(n + 1, 1);
  function<void(int, int)> dfs = [&](int u, int p) {
    for (int v : adj[u]) if (v != p)
      dfs(v, u), siz[u] += siz[v];
  };
  dfs(1, 1);
  
  int u, t = 1;
  do {
    u = t;
    for (int v : adj[u])
      if (siz[v] < siz[u] and siz[v] * 2 > n) t = v;
  } while (t != u);
  cout << u << '\n';
}
