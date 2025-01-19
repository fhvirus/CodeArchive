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

  int t;
  cin >> t;

  while (t --> 0) {
    int n;
    cin >> n;

    bool win = false;
    for (int x; n--; ) {
      cin >> x;
      win |= (x % 2 != 0);
    }

    cout << (win ? "first\n" : "second\n");
  }
}
