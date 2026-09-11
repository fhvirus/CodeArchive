#include <bits/stdc++.h>
using namespace std;

#include <boost/unordered/unordered_flat_map.hpp>

struct Value {
  int n, h; uint64_t sum;
  auto operator < (const Value& o) const { return tie(n, sum) < tie(o.n, o.sum); }
};
struct Source { int i, p; };

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int M;
  uint64_t C;
  cin >> M >> C;

  vector<uint64_t> A(M);
  for (auto &i : A) cin >> i;
  if (C == 1) { cout << "1\n" << (ranges::min_element(A) - begin(A)) << '\n'; exit(0); }
  {
    auto t = C;
    for (auto &i : A) t /= gcd(t, i);
    if (t > 1) { cout << "-1\n"; exit(0); }
  }

  vector<Source> hist;
  boost::unordered_flat_map<uint64_t, Value> sc, dp;
  sc[C] = {0, -1, 0};
  for (int i = 0; i < M; ++i) {
    if (gcd(C, A[i]) == 1) continue;
    dp = sc;
    for (auto [pc, pval] : sc) {
      uint64_t c = pc / gcd(A[i], pc);
      if (c == pc) continue;
      Value val {pval.n + 1, (int)size(hist), pval.sum + A[i]};
      if (not dp.count(c) or val < dp.at(c))
        dp[c] = val, hist.push_back({i, pval.h});
    }
    sc.swap(dp);
  }

  if (not sc.count(1)) { cout << -1 << '\n'; exit(0); }
  auto ans = sc.at(1);
  cout << ans.n << '\n';
  for (int h = ans.h; h != -1; h = hist[h].p)
    cout << hist[h].i << " \n"[hist[h].p == -1];

  return 0;
}
