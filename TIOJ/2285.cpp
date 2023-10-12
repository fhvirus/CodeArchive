#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Line {
  mutable ll k, m, p;
  bool operator<(const Line& o) const { return k < o.k; }
  bool operator<(ll x) const { return p < x; }
};
struct LineContainer : multiset<Line, less<>> {
  static const ll inf = LLONG_MAX;
  ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
  bool isect(iterator x, iterator y) {
    if (y == end()) return x->p = inf, 0;
    if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
    else x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
  void add(ll k, ll m) {
    auto z = insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
  }
  ll query(ll x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, K;
  cin >> N >> K;

  vi a(N+1), b(N+1), m(N+1);
  rep (i, 0, N+1) cin >> a[i];
  rep (i, 1, N+1) cin >> b[i];
  rep (i, 1, N+1) cin >> m[i];

  const int BS = N / K + 1;
  vector<vector<pii>> pre(BS), suf(BS);
  rep (i, 1, N+1) {
    int l = max((b[i] - K + 1), 0), r = b[i];
    pre[r / K].emplace_back(r, i);
    if (l / K < r / K)
      suf[l / K].emplace_back(l, i);
  }

  vector<ll> dp(N+1, LLONG_MIN / 2);
  dp[0] = 0;

  LineContainer hull;
  rep (b, 0, BS) {
    int lb = b * K, rb = min((b + 1) * K - 1, N);

    sort(all(pre[b]));
    hull.clear();
    int ptr = lb - 1;
    for (const auto& [pos, id]: pre[b]) {
      while (ptr < pos) {
        ptr += 1;
        dp[ptr] += (a[ptr] + 1ll) * m[ptr];
        hull.add(-a[ptr], dp[ptr]);
      }
      dp[id] = max(dp[id], hull.query(m[id]));
    }
    while (++ptr <= rb) dp[ptr] += (a[ptr] + 1ll) * m[ptr];

    sort(all(suf[b]), greater<pii>());
    hull.clear();
    ptr = rb + 1;
    for (const auto& [pos, id]: suf[b]) {
      while (ptr > pos) {
        ptr -= 1;
        hull.add(-a[ptr], dp[ptr]);
      }
      dp[id] = max(dp[id], hull.query(m[id]));
    }
  }

  int ans = (int) (accumulate(all(dp), (__int128) 0) % 1020050909);
  cout << ans + (ans < 0 ? 1020050909 : 0) << '\n';

  return 0;
}
