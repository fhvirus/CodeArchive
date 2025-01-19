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

  // const int m = 1000000;
  // const int c = (1 << 10);
  // vi sg(m + 1);
  // for (int i = 3; i <= m; ++i) {
  //   bitset<c> has;
  //   has.set();
  //   for (int j = 1, k = i - 1; j < k; ++j, --k)
  //     has[sg[j] ^ sg[k]] = 0;
  //   sg[i] = has._Find_first();
  //   if (sg[i] == 0) cout << i << ' ';
  // }
  // cout << endl;
  // return 0;

  // compile with -Ofast, ran for about 5min
  // these are the only x's with sg(x) = 0:
  const set<int> lose = {1, 2, 4, 7, 10, 20, 23, 26, 50, 53,
    270, 273, 276, 282, 285, 288, 316, 334, 337, 340,
    346, 359, 362, 365, 386, 389, 392, 566, 630, 633,
    636, 639, 673, 676, 682, 685, 923, 926, 929, 932, 1222};

  int t;
  cin >> t;

  while (t --> 0) {
    int n;
    cin >> n;
    cout << (lose.count(n) == 0 ? "first\n" : "second\n");
  }
}
