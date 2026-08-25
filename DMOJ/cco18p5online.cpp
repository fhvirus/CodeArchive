#include <bits/stdc++.h>
using namespace std;

struct Solver {
  int N, K, S, B, Kb;
  vector<int> a, bmax, bans, tmp, maxans;
  int sweep(int lb, int rb) {
    if (K <= 1) return -1;
    int ans = -1;
    for (int qh = 0, qt = 0, i = lb; i < rb; ++i) {
      while (qh < qt and tmp[qh] + K <= i) ++qh;
      if (qh < qt) ans = max(ans, a[i] + a[tmp[qh]]);
      while (qh < qt and a[tmp[qt - 1]] <= a[i]) --qt;
      tmp[qt++] = i;
    }
    return ans;
  }
  void calc(int bi, bool inb) {
    const int lb = S * bi, rb = min(S * (bi + 1), N);
    bmax[bi] = *max_element(begin(a) + lb, begin(a) + rb);
    if (inb) bans[bi] = sweep(lb, rb);
    int ans = bans[bi];
    int to = (bi + max(Kb, 1)) * S, pmax = -1;
    for (int i = max({rb - K, to - K, lb}); i < rb; ++i) {
      while (to < N and i + K > to) pmax = max(pmax, a[to++]);
      ans = max(ans, a[i] + pmax);
    }
    maxans[B + bi] = ans;
    for (int i = (B + bi) / 2; i > 0; i /= 2)
      maxans[i] = max(maxans[i * 2], maxans[i * 2 + 1]);
  }
  Solver(int _N, int _K, int _S, auto& _a): N(_N), K(_K),
    S(_S), B((N + S - 1) / S), Kb(K / S),
    a(_a), bmax(B), bans(B), tmp(S), maxans(B * 2, -1) {
    for (int bi = 0; bi < B; ++bi) calc(bi, true);
  }
  void modify(int i, int x) {
    a[i] = x;
    const int bi = i / S;
    calc(bi, true);
    const int lb = i - (K - 1), rb = (bi + 1) * S - K;
    if (0 <= lb and lb < bi * S) calc(lb / S, false);
    if (0 <= rb and rb < bi * S) calc(rb / S, false);
  }
  int get_ans() const { return maxans[1]; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, K, Q;
  cin >> N >> K >> Q;

  vector<int> a(N);
  for (int &i : a) cin >> i;

  const int kB = 10;
  int pans = -1;
  vector<Solver> solvers;
  solvers.emplace_back(N, K, kB, a);
  while (true) {
    const auto &s = solvers.back();
    pans = max(pans, s.get_ans());
    if (s.B <= 1 or s.Kb <= 1) break;
    solvers.emplace_back(s.B, s.Kb, kB, s.bmax);
  }
  cout << pans << '\n';

  for (int i, x; Q --> 0; ) {
    cin >> i >> x;
    i = (i ^ pans) - 1; x ^= pans;

    solvers[0].modify(i, x);
    for (int j = 1; j < (int)size(solvers); ++j) {
      i /= solvers[j - 1].S;
      solvers[j].modify(i, solvers[j - 1].bmax[i]);
    }

    pans = -1;
    for (auto &s : solvers) pans = max(pans, s.get_ans());
    cout << pans << '\n';
  }

  return 0;
}
