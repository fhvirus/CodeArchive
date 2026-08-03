#include <bits/stdc++.h>
using namespace std;

const char types[] = "MFBX";
int type_id(char c) { return (c == 'M' ? 0 : (c == 'F' ? 1 : 2)); }
int get_id(int a, int b, int c, int d) { return ((a * 4 + b) * 4 * 4 + (c * 4 + d)); }

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  string s;
  cin >> s;

  vector<int> dp(4 * 4 * 4 * 4, INT_MIN);
  auto sc = dp;
  sc[get_id(3, 3, 3, 3)] = 0;

  for (char c : s) {
    ranges::fill(dp, INT_MIN);
    int t = type_id(c);
    for (int i : {0, 1, 2, 3}) for (int j : {0, 1, 2, 3})
        for (int k : {0, 1, 2, 3}) for (int l : {0, 1, 2, 3}) {
          int id = get_id(i, j, k, l);
          {
            int v = (i != 3) + (j != 3 and j != i) + (t != i and t != j);
            int to = get_id(j, t, k, l);
            dp[to] = max(dp[to], sc[id] + v);
          }
          {
            int v = (k != 3) + (l != 3 and l != k) + (t != k and t != l);
            int to = get_id(i, j, l, t);
            dp[to] = max(dp[to], sc[id] + v);
          }
        }
    swap(dp, sc);
  }

  cout << *ranges::max_element(sc) << '\n';

  return 0;
}
