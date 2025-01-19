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

  const int kC = 1000001;
  vi cnt(kC);
  rep (i, 1, kC) for (int j = i; j < kC; j += i) cnt[j] += 1;

  int n;
  cin >> n;
  for (int x; n--; ) {
    cin >> x;
    cout << cnt[x] << '\n';
  }
}
