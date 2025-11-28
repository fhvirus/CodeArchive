#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M;
  cin >> N >> M;

  vector<int64_t> P(M), R(M);
  for (auto &i : P) cin >> i;
  for (auto &i : R) cin >> i;

  map<int64_t, int> naked;
  naked[0] = 0;

  vector<int> dress(M, INT_MIN);
  for (int i = 0; i < N; ++i) {
    int C;
    int64_t T;
    cin >> C >> T;
    C -= 1;

    int v = dress[C] + 1;

    if (T - P[C] >= 0)
      v = max(v, prev(naked.upper_bound(T - P[C]))->second + 1);

    int64_t t = T + R[C];
    auto it = naked.find(t);
    if (it != end(naked) and it->second < v)
      naked.erase(it);

    it = naked.upper_bound(t);
    if (prev(it)->second < v) {
      while (it != end(naked) and it->second <= v)
        it = naked.erase(it);
      naked[t] = v;
    }

    dress[C] = v;
  }

  cout << prev(end(naked))->second << '\n';

  return 0;
}
