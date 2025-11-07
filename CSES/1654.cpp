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
  cin >> n;

  vi x(n);
  for (int &i : x) cin >> i;

  const int L = __lg(*max_element(all(x))) + 1;
  const int m = (1 << L);
  vi cnt(m);
  for (int i : x) cnt[i] += 1;

  vi sub = cnt;
  rep (l, 0, L) rep (i, 0, m) if (i >> l & 1)
    sub[i] += sub[i ^ (1 << l)];

  rep (l, 0, L) rep (i, 0, m) if (~i >> l & 1)
    cnt[i] += cnt[i ^ (1 << l)];

  int mask = (1 << L) - 1;
  for (int i : x) {
    cout << sub[i] << ' '
         << cnt[i] << ' '
         << n - sub[(~i & mask)] << '\n';
  }

  return 0;
}
