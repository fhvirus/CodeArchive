#include <bits/stdc++.h>
using namespace std;

void order(auto& e) {
  ranges::sort(e); // 唬爛
  e.erase(ranges::unique(e).begin(), end(e));
}

int solve(auto& e, uint64_t need, int best) {
  if (need == 0) return 0;
  if (empty(e) or best <= 1) return best;
  uint64_t u = e.back(); e.pop_back();
  {
    uint64_t t = (need & ~u);
    vector<uint64_t> ne;
    for (auto i : e) if (t & i) ne.push_back(t & i);
    order(ne);
    best = solve(ne, t, best - 1) + 1;
  }
  uint64_t tot = accumulate(begin(e), end(e), 0ul, bit_or());
  if ((tot & need) == need) best = solve(e, need, best);
  return best;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (int n, m; cin >> n >> m, n != 0; ) {
    vector<uint64_t> e(n);
    for (int u, v, i = 0; i < m; ++i) {
      cin >> u >> v; --u, --v;
      e[u] |= (1l << v);
      e[v] |= (1l << u);
    }
    for (int i = 0; i < n; ++i)
      e[i] |= (1l << i);
    order(e);
    cout << solve(e, (1l << n) - 1, INT_MAX) << '\n';
  }

  return 0;
}
