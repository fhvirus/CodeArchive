#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m, k;
  cin >> n >> m >> k;

  map<string, int> type;
  for (int i = 0; i < k; ++i) {
    string s;
    cin >> s;
    type[s] = i;
  }

  vector<vector<pair<int, int>>> adj(n + 1);
  vector<int> type_e(m);

  for (int x, y, i = 0; i < m; ++i) {
    string s;
    cin >> x >> y >> s;
    type_e[i] = type[s];
    adj[x].emplace_back(y, i);
    adj[y].emplace_back(x, i);
  }

  vector<int> num(n + 1), stk, tdj(k);
  int tid = 0, need = 0;

  const auto process = [&](vector<int> es) {
    map<int, int> cnt;
    for (int &e : es) cnt[type_e[e]] += 1;
    es.clear();
    for (auto [i, c] : cnt) {
      if (c >= 2) need |= (1 << i);
      else es.push_back(i);
    }
    for (int i : es) for (int j : es) tdj[i] |= (1 << j);
  };

  const auto dfs = [&](const auto& dfs, int u, int p) -> int {
    int me = num[u] = ++tid, low = me;
    for (auto [v, e] : adj[u]) if (e != p) {
      if (num[v]) {
        low = min(low, num[v]);
        if (num[v] < me)
          stk.push_back(e);
      } else {
        int si = (int) stk.size();
        int up = dfs(dfs, v, e);
        low = min(low, up);
        if (up == me) {
          stk.push_back(e);
          process(vector<int>(begin(stk) + si, end(stk)));
          stk.resize(si);
        }
        else if (up < me) stk.push_back(e);
        else need |= (1 << type_e[e]);
      }
    }
    return low;
  };

  dfs(dfs, 1, -1);
  for (int i = 0; i < k; ++i) tdj[i] &= ~(1 << i);

  int min_num = k, num_can = 0;
  for (int i = need; i < (1 << k); ++i) if ((need & i) == need) {
    int t = 0;
    for (int j = 0; j < k; ++j) if ((i >> j & 1) == 0) t |= ((~i) & tdj[j]);
    if (t == 0) {
      num_can += 1;
      min_num = min(min_num, __builtin_popcount(i));
    }
  }

  cout << min_num << '\n' << num_can << '\n';

  return 0;
}
