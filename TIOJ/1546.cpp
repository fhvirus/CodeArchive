#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M, P, Q;
  cin >> N >> M >> P >> Q;

  vector<int> ub(M), lb(M);
  for (int &i : ub) cin >> i;
  lb[0] = ub[0];
  for (int i = 1; i < M; ++i) cin >> lb[i];

  int64_t turn = (M - 1) * (M - 1);
  for (int _ : {0, 1}) {
    for (int i = 0; i < M; ++i) {
      int last = ub[0] ^ lb[i] ^ ub[0], len = 1;
      for (int j = 1; j < M; ++j) {
        int cur = last ^ ub[j - 1] ^ ub[j];
        if (last > cur) len = 0;
        len += 1, last = cur;
        if (P <= len) turn += min(Q, len) - P + 1;
      }
    }
    swap(lb, ub);
  }

  cout << turn % N << '\n';

  return 0;
}
