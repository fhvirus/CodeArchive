#include <bits/stdc++.h>
using namespace std;

struct Seguki {
  int n;
  vector<int> val;
  Seguki(int _n) : n(_n), val(n * 2) {}
  void modify(int p, int v) {
    for (val[p += n] = v; p >>= 1; )
      val[p] = max(val[p * 2], val[p * 2 + 1]);
  }
  int query(int l, int r) {
    int res = INT_MIN;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) res = max(res, val[l++]);
      if (r & 1) res = max(res, val[--r]);
    }
    return res;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;

  map<int, set<int>> mp;

  vector<int> x(n);
  Seguki sgk(n);
  for (int i = 0; i < n; ++i) {
    cin >> x[i];
    sgk.modify(i, mp.count(x[i]) ? *prev(end(mp.at(x[i]))) : -1);
    mp[x[i]].insert(i);
  }
  for (int t, a, b; q --> 0; ) {
    cin >> t >> a >> b;
    a -= 1;
    if (t == 1) {
      { 
        auto& s = mp[x[a]];
        auto it = s.find(a), nx = next(it);
        if (nx != end(s))
          sgk.modify(*nx, it == begin(s) ? -1 : *prev(it));
        s.erase(it);
      }
      x[a] = b;
      {
        auto& s = mp[x[a]];
        auto it = s.insert(a).first, nx = next(it);
        if (nx != end(s))
          sgk.modify(*nx, a);
        sgk.modify(a, it == begin(s) ? -1 : *prev(it));
      }
    } else cout << (sgk.query(a, b) < a ? "YES\n" : "NO\n");
  }

  return 0;
}
