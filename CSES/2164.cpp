#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int query(int n, int k) {
  if (k * 2 <= n) return k * 2;
  if (n == 1) return 1;
  int p = query(n - n / 2, k - n / 2);
  return n % 2 == 0 ? 2 * p - 1 : 
    (p == 1 ? n : 2 * p - 3);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int q;
  cin >> q;

  while (q --> 0) {
    int n, k;
    cin >> n >> k;
    cout << query(n, k) << '\n';
  }
}
