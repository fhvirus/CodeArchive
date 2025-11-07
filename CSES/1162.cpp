#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct BIT {
  vi val;
  BIT(int n) : val(n) {}
  void modify(int p, int v) {
    for (; p < sz(val); p += p & -p)
      val[p] += v;
  }
  int query(int p) {
    int v = 0;
    for (; p > 0; p -= p & -p)
      v += val[p];
    return v;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vi p(n);
  for (int &i : p) cin >> i;

  { // Subtask 1
    BIT bit(n + 1);
    ll ans = 0;
    rep (i, 0, n) {
      ans += (i - bit.query(p[i]));
      bit.modify(p[i], 1);
    }
    cout << ans << ' ';
  } { // Subtask 2
    int ans = 0;
    vi a = p; a.insert(begin(a), 0);
    for (int i = 1; i <= n; ++i) {
      while (a[i] != i) {
        int t = a[i];
        swap(a[i], a[t]);
        ans += 1;
      }
    }
    cout << ans << ' ';
  } { // Subtask 3
    vi lis;
    for (int i : p) {
      auto it = lower_bound(all(lis), i);
      if (it == end(lis)) lis.push_back(i);
      else *it = i;
    }
    cout << n - sz(lis) << ' ';
  } { // Subtask 4
    int ans = 0, pre = 0;
    for (int i : p) {
      if (i < pre) ans = max(ans, i);
      pre = max(pre, i);
    }
    cout << ans << '\n';
  }

  return 0;
}
