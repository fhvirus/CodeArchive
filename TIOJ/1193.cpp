#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (int N, M; cin >> N >> M, M; ) {
    int64_t ans = (N < M);
    for (int i = 1; i <= N and ans > 0; ++i)
      ans = ans * i % M;
    cout << ans << '\n';
  }

  return 0;
}
