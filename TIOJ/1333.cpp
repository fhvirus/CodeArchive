#include <bits/stdc++.h>
using namespace std;

const int kM = 200;
typedef bitset<200> bs;

int solve(vector<bs>& a, int need, int best) {
  if (need == 0) return 0;
  if (empty(a) or best <= 1) return best;
  bs u = a.back(); a.pop_back();
  {
    vector<bs> b;
    bs c;
    for (auto &i : a)
      if ((i & u).none())
        b.push_back(i), c |= i;
    if (c.count() == need - u.count())
      best = 1 + solve(b, need - (int) u.count(), best - 1);
  }
  return solve(a, need, best);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M;
  cin >> N >> M;

  vector<bs> a(N);
  for (int i = 0; i < N; ++i)
    for (int b, j = 0; j < M; ++j) {
      cin >> b;
      if (b) a[i].set(j);
    }

  ranges::sort(a, [](bs u, bs v) { return u.count() < v.count(); });
  
  cout << solve(a, M, INT_MAX) << '\n';

  return 0;
}
