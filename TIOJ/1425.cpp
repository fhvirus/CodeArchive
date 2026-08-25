#include <bits/stdc++.h>
using namespace std;

const int kN = 10'000'001;
int pf[kN];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int Nmax, Q;
  cin >> Nmax >> Q;

  for (int i = 2; i <= Nmax; ++i) if (pf[i] == 0)
    for (int j = i; j <= Nmax; j += i)
      pf[j] += 1;

  for (int n; Q --> 0; ) {
    cin >> n;
    int64_t ans = 0;
    for (int lb = 1, rb = 1; lb <= n; lb = rb + 1) {
      int t = n / lb;
      rb = n / t;
      ans = max(ans, (1l << (4 * pf[t])) + rb);
    }
    cout << ans << '\n';
  }

  return 0;
}
