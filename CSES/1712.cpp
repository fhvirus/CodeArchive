#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

ll modpow(ll x, ll e, ll mod) {
  ll r = 1;
  for (; e > 0; e >>= 1, x = x * x % mod)
    if (e & 1) r = r * x % mod;
  return r;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int q;
  cin >> q;

  const int MOD = 1e9 + 7;

  while (q --> 0) {
    int a, b, c;
    cin >> a >> b >> c;
    cout << modpow(a, modpow(b, c, MOD - 1), MOD) << '\n';
  }
}
