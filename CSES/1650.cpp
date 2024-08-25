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

  int n, q;
  cin >> n >> q;

  vi x(n);
  for (int &i : x) cin >> i;
  partial_sum(all(x), begin(x), bit_xor<>());

  for (int a, b; q--; ) {
    cin >> a >> b;
    cout << (x[b - 1] ^ (a > 1 ? x[a - 2] : 0)) << '\n';
  }
}
