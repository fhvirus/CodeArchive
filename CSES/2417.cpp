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

  vector<ll> cnt(*max_element(all(x)) + 1);
  for (int i : x) cnt[i] += 1;
  rep (i, 1, sz(cnt)) for (int j = i + i; j < sz(cnt); j += i) cnt[i] += cnt[j];
  for (int i = sz(cnt) - 1; i >= 1; --i) {
    cnt[i] = cnt[i] * (cnt[i] - 1) / 2;
    for (int j = i + i; j < sz(cnt); j += i)
      cnt[i] -= cnt[j];
  }

  cout << cnt[1] << '\n';
}
