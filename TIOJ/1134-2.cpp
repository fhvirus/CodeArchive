#include <bits/stdc++.h>
using namespace std;

const int kN = 202;
int a[kN][kN], eek[kN], stk[kN], pos[kN];

void solve() {
  int N, M;
  cin >> N >> M;
  
  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= M; ++j) {
      cin >> a[i][j];
      a[i][j] = a[i - 1][j] + (a[i][j] ? -1 : 1);
    }

  int ans = 0;
  for (int d = 1; d <= N; ++d)
    for (int u = 0; u < d; ++u) {
      for (int i = 1; i <= M; ++i)
        eek[i] = eek[i - 1] + a[d][i] - a[u][i];

      int top = 1;
      for (int i = 1; i <= M; ++i) {
        if (eek[i] < stk[top - 1]) {
          stk[top] = eek[i];
          pos[top] = i;
          ++top;
        } else if (eek[i] > stk[top - 1]) {
          int p = (int) (upper_bound(stk, stk + top, eek[i], greater<int>()) - stk);
          ans = max(ans, (d - u) * (i - pos[p]));
        }
      }
    }

  cout << ans << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T --> 0) solve();

  return 0;
}
