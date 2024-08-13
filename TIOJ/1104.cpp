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

  string s;
  bool empty = true;
  map<string, int> mp;
  vector<vi> adj, adv;

  auto get_id = [&]() -> int {
    cin >> s;
    if (mp.count(s) == 0) {
      mp[s] = sz(adj);
      adj.emplace_back();
      adv.emplace_back();
    }
    return mp[s];
  };

  auto solve = [&]() -> bool {
    int n = sz(adj);
    vector<vi> can_reach(n);
    for (int i = 0; i < n; ++i) {
      vector<bool> vis(n, false);
      can_reach[i].push_back(i);
      for (int h = 0; h < sz(can_reach[i]); ++h) {
        int u = can_reach[i][h++];
        for (int v : adj[u])
          if (not vis[v]) vis[v] = true, can_reach[i].push_back(v);
        for (int v : adv[u])
          if (not vis[v]) vis[v] = true, can_reach[i].push_back(v);
      }
      can_reach[i].erase(begin(can_reach[i]));
    }
    for (int i = 0; i < n; ++i)
      for (int j : adv[i])
        if (find(all(can_reach[j]), i) != end(can_reach[j])) return false;
    return true;
  };

  while (cin >> s >> ws) {
    if (s == "=====") {
      if (empty) break;
      cout << (solve() ? "Accept\n" : "Reject\n");
      empty = true;
      mp.clear(); adj.clear(); adv.clear();
    } else {
      empty = false;
      bool is_adv = (s == "advice");
      if (is_adv) cin >> s >> s;
      int u = get_id(); cin >> s;
      while (cin.get() != '\n') {
        int v = get_id();
        (is_adv ? adv : adj)[u].push_back(v);
      }
    }
  }

  return 0;
}
