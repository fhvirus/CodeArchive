#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (int n, h; cin >> n; ) {
    priority_queue<int> pq;
    int64_t sum = 0;
    for (int a, i = 0; i < n; ++i) {
      cin >> a;
      sum += a;
      pq.push(a);
    }
    cin >> h;

    while (not empty(pq) and h >= 0) {
      int64_t a = pq.top(); pq.pop();
      sum -= a;
      a -= min(max(100l, a * 4 / 10), a);
      if (a > 0) sum += a, pq.push(a);
      h -= min<int>(sum / 10, h + 1);
    }
    if (h >= 0) cout << "yes\n" << h << '\n';
    else cout << "no\n" << sum << '\n';
  }

  return 0;
}
