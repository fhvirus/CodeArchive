#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int kN = 2002;

vector<vector<int>> adj;
vector<int> pre, low;
int tot;
void tarjan(int u, int p, int e, vector<int> &isAP){
  pre[u] = low[u] = ++tot;
  int ch = 0;
  for(int v: adj[u]){
    if(v == p or v == e) continue;
    if(pre[v] == 0){
      ++ch;
      tarjan(v, u, e, isAP);
      low[u] = min(low[u], low[v]);
      if(low[v] >= pre[u])
        isAP[u] = 1;
    } else if(pre[v] < pre[u])
      low[u] = min(low[u], pre[v]);
  }
  if(u == p and ch == 1)
    isAP[u] = 0;
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M;
  cin >> N >> M;

  adj.resize(N+1);
  for (int u, v, i = 0; i < M; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  set<pii> es;
  for (int _ = 0; _ < 3; ++_) {
    queue<int> q;
    vector<bool> vis(N + 1);
    for (int i = 1; i <= N; ++i) if (not vis[i]) {
      q.push(i), vis[i] = true;
      while (not q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) if (not vis[v])
          q.push(v), vis[v] = true, es.emplace(u, v), es.emplace(v, u);
      }
    }
    for (auto [u, v] : es) {
      auto it = find(all(adj[u]), v);
      if (it != end(adj[u])) adj[u].erase(it);
    }
  }

  adj.clear();
  adj.resize(N+1);
  for (auto [u, v] : es)
    adj[u].push_back(v);

  int ans = 0;
  vector<int> isAP(N+1, 0);

  pre.assign(N+1, 0);
  low.assign(N+1, 0);
  tot = 0;
  tarjan(1, 1, 0, isAP);

  for(int i = 1; i < N; ++i) {
    fill(all(pre), 0);
    fill(all(low), 0);
    tot = 0;

    vector<int> tmp(N+1, 0);
    int cp = 0, lone = 0;
    for(int v: adj[i]){
      if(pre[v] != 0) continue;
      ++cp; lone += (sz(adj[v]) == 1 and v > i);
      tarjan(v, v, i, tmp);
    }
    if(isAP[i]) ans += N - i - ((cp == 2) ? lone : 0);
    else {
      for(int j = i+1; j <= N; ++j)
        if(tmp[j] == 1) ++ans;
    }
  }
  cout << ans << '\n';

  return 0;
}
