#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, x, a, b;
  cin >> n >> x;
  a = n / 2, b = n - n / 2;

  const auto calc = [&](int a) {
    vi v(a), sum(1 << a);
    for (int &i : v) cin >> i;
    rep (i, 1, (1 << a)) {
      sum[i] = sum[i ^ (i & -i)] + v[__lg(i & -i)];
      if (sum[i] > x) sum[i] = x + 1;
    }
    sort(all(sum));
    return sum;
  };

  auto va = calc(a), vb = calc(b);

  ll ans = 0;
  for (int i : va)
    ans += int(upper_bound(all(vb), x - i) - lower_bound(all(vb), x - i));

  cout << ans << '\n';

  return 0;
}
