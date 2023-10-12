#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#ifdef NONTOI
#define debug(args...) LKJ("\033[1;32m["#args"]\033[0m", args)
template<class I> void LKJ(I&&x){ cerr << x << '\n'; }
template<class I, class...T> void LKJ(I&&x, T&&...t)
{ cerr << x << ", ", LKJ(t...); }
template<class I> void print(I a, I b)
{ while(a < b) cerr << *a << " \n"[next(a) == b], ++a; }
#else
#define debug(...) 0
#define print(...) 0
#endif

void solve(int N) {
  vector<ll> P(N), F(N);
  ll mnv = LLONG_MAX, mxv = LLONG_MIN;
  rep (i, 0, N) {
    cin >> P[i] >> F[i];
    mnv = min(mnv, F[i]);
    mxv = max(mxv, F[i]);
  }

  ll ans = mnv;
  for (ll l = 1ll << 40; l >>= 1; ) if (ans + l <= mxv) {
    ll t = ans + l, left = 0;
    rep (i, 0, N) {
      if (i > 0) left = (left >= 0ll ? max(0ll, left - (P[i] - P[i-1])) : left - (P[i] - P[i-1]));
      left += F[i] - t;
    }
    if (left >= 0) ans = t;
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int N;
  while (cin >> N) solve(N);
  return 0;
}
