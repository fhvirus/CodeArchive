#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  double A, B;
  while (cin >> A >> B) {
    int n;
    cin >> n;

    vector<pair<double, double>> is(n);
    for (auto &[l, r] : is) cin >> l >> r;

    vector<int> ids(n), ans;
    iota(begin(ids), end(ids), 0);
    ranges::sort(ids, [&](int u, int v) { return is[u] < is[v]; });

    double cur = A;
    for (int i = 0; cur < B or ans.empty(); ) {
      pair<double, int> best(cur, -1);
      for (; i < n and is[ids[i]].first <= cur; ++i)
        best = max(best, make_pair(is[ids[i]].second, ids[i]));
      if (best.second == -1) { ans.clear(); break; }
      cur = best.first;
      ans.push_back(best.second);
    }

    if (ans.empty()) cout << "impossible\n";
    else {
      cout << size(ans) << '\n';
      for (int i : ans) cout << i << " \n"[i == ans.back()];
    }
  }

  return 0;
}
