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

  int n;
  ll k;
  cin >> n >> k;

  vi x(n * 2);
  rep (i, 0, n) cin >> x[i];
  rep (i, 0, n) x[i + n] = x[i];

  const int L = __lg(n) + 1;
  vector<vi> jmp(L, vi(n * 2));
  {
    ll sum = 0;
    for (int i = 0, j = 0; i < n * 2; sum -= x[i++]) {
      while (j < n * 2 and sum + x[j] <= k)
        sum += x[j++];
      jmp[0][i] = j;
    }
    rep (l, 1, L) rep (i, 0, n * 2)
      jmp[l][i] = (jmp[l - 1][i] < n * 2 ? jmp[l - 1][jmp[l - 1][i]] : n * 2);
  }

  int ans = n;
  rep (i, 0, n) {
    int j = i, cur = 0;
    for (int l = L - 1; l >= 0; --l)
      if (jmp[l][j] < i + n)
        cur += (1 << l), j = jmp[l][j];
    ans = min(ans, cur + 1);
  }
  cout << ans << '\n';

  return 0;
}
