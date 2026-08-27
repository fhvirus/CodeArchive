#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (int n; cin >> n, n != 0; ) {
    vector<int> sit(19, -1);
    vector<pair<int, string>> person(19);
    for (int t, w, i = 0; i < n; ++i) {
      string name; cin >> name >> t >> w;
      if (sit[t + w] <= t)
        sit[t + w] = t, person[t + w] = pair(i, name);
    }

    int need = 0, period = 1;
    for (int i = 1; i <= 18; ++i) if (sit[i] != -1) {
      need += 1;
      if (sit[i] == i) period = lcm(period, i);
    }

    int ans = 0;
    while (true) {
      ans += period;
      int cnt = 0;
      for (int i = 1; i <= 18; ++i) if (sit[i] != -1) {
        int k = ans % i;
        if (k == 0 or k >= sit[i])
          cnt += 1;
      }
      if (cnt == need) break;
    }

    pair<int, string> latest(-1, "");
    for (int i = 1; i <= 18; ++i) if (ans % i == sit[i] % i)
      latest = max(latest, person[i]);

    cout << latest.second << " finally comes " << ans << " minutes later\n";
  }

  return 0;
}
