// Actually wrong due to geometry, see problem discussion
#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (int N, M; cin >> N, N != 0; ) {
    cin >> M;
    int64_t ans = (int64_t) N * (N - 1) * (N - 2) / 6;
    for (int64_t K; M --> 0; ) {
      cin >> K;
      ans -= K * (K - 1) * (K - 2) / 6;
    }
    if (ans <= 0) cout << "IMPOSSIBLE\n";
    else cout << ans << '\n';
  }

  return 0;
}
