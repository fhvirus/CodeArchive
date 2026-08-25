#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, K, Q;
  cin >> N >> K >> Q;

  vector<int> a(N);
  for (int &i : a) cin >> i;

  const int S = (int)ceil(sqrt(N));
  const int B = (N + S - 1) / S;
  const int Kb = K / S;

  vector<int> bans(B), bmax(B);

  vector<int> tmp(max(S, B));
  const auto sweep = [&tmp](auto& v, int lb, int rb, int len) {
    int ans = -1;
    for (int qh = 0, qt = 0, i = lb; i < rb; ++i) {
      while (qh < qt and tmp[qh] + len <= i) ++qh;
      if (qh < qt) ans = max(ans, v[i] + v[tmp[qh]]);
      while (qh < qt and v[tmp[qt - 1]] <= v[i]) --qt;
      tmp[qt++] = i;
    }
    return ans;
  };
  const auto calc = [&](int bi) {
    const int lb = S * bi, rb = min(S * (bi + 1), N);
    int ans = sweep(a, lb, rb, K);
    bmax[bi] = *max_element(begin(a) + lb, begin(a) + rb);
    int to = (bi + max(Kb, 1)) * S, pmax = -1;
    for (int i = max({rb - K, to - K, lb}); i < rb; ++i) {
      while (to < N and i + K > to) pmax = max(pmax, a[to++]);
      ans = max(ans, a[i] + pmax);
    }
    bans[bi] = ans;
  };
  const auto get_ans = [&]()
  { return max(sweep(bmax, 0, B, Kb), *ranges::max_element(bans)); };

  for (int i = 0; i < B; ++i) calc(i);
  cout << get_ans() << '\n';

  for (int i, x; Q --> 0; ) {
    cin >> i >> x; i -= 1;
    a[i] = x;

    const int bi = i / S;
    calc(bi);

    const int lb = i - (K - 1), rb = (bi + 1) * S - K;
    if (0 <= lb and lb < bi * S) calc(lb / S);
    if (0 <= rb and rb < bi * S) calc(rb / S);

    cout << get_ans() << '\n';
  }

  return 0;
}
