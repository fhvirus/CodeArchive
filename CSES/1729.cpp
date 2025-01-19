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

  int n, k;
  cin >> n >> k;

  vi p(k);
  for (int &i : p) cin >> i;

  vector<bool> wl(n + 1);
  wl[0] = 0;

  rep (i, 1, n + 1)
    for (int j : p) if (j <= i)
      wl[i] = wl[i] or not wl[i - j];

  rep (i, 1, n + 1) cout << "LW"[wl[i]];
  cout << '\n';
}
