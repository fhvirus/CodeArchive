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

  double ans = 0;
  for (int i = 1; i <= k; ++i)
    ans += i * (pow(1.0 * i / k, n) - pow(1.0 * (i - 1) / k, n));

  cout << setprecision(6) << fixed << roundeven(ans * 1e6) / 1e6 << '\n';
}
