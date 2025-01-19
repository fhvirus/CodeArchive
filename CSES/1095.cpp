#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int MOD = 1e9 + 7;
ll modpow(ll x, int e) {
  ll r = 1;
  for (; e > 0; e >>= 1, x = x * x % MOD)
    if (e & 1) r = r * x % MOD;
  return r;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int q;
  cin >> q;

  while (q --> 0) {
    int a, b;
    cin >> a >> b;
    cout << modpow(a, b) << '\n';
  }
}
