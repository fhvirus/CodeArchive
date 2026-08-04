#include <bits/stdc++.h>
using namespace std;

typedef bitset<200> bs;

void order(auto& e) {
  // ranges::sort(e);
  e.erase(ranges::unique(e).begin(), end(e));
}

int solve(auto& e, bs need, int best) {
  if (need == 0) return 0;
  if (empty(e) or best <= 1) return best;
  bs u = e.back(); e.pop_back();
  {
    bs t = (need & ~u);
    vector<bs> ne;
    for (auto i : e) if ((t & i).any()) ne.push_back(t & i);
    order(ne);
    best = solve(ne, t, best - 1) + 1;
  }
  bs tot = accumulate(begin(e), end(e), bs(), bit_or());
  if ((tot & need) == need) best = solve(e, need, best);
  return best;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (int n, m; cin >> n >> m; ) {
    vector<bs> e(n);
    bs need;
    for (int u, v, i = 0; i < m; ++i) {
      cin >> u >> v;
      e[u].set(i);
      e[v].set(i);
      need.set(i);
    }
    order(e);
    cout << solve(e, need, INT_MAX) << '\n';
  }

  return 0;
}
