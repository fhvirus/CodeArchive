#include <bits/stdc++.h>
using namespace std;

int get_val(char op, int u, int v) {
  if (op == '+') return u + v;
  if (op == '-') return u - v;
  return u * v;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string s;
  cin >> s;

  vector<int> val;
  string op;

  {
    int cur = 0;
    for (char c : s) {
      if (isdigit(c)) cur = cur * 10 + (c - '0');
      else {
        val.push_back(cur);
        cur = 0;
        op.push_back(c);
      }
    }
    val.push_back(cur);
  }

  int n = (int) val.size();
  vector max_val(n, vector<int>(n, INT_MIN));
  vector min_val(n, vector<int>(n, INT_MAX));
  for (int i = 0; i < n; ++i)
    max_val[i][i] = min_val[i][i] = val[i];

  for (int len = 1; len < n; ++len) {
    for (int l = 0, r = len; r < n; ++l, ++r) {
      for (int m = l + 1; m <= r; ++m) {
        for (int vl : {max_val[l][m-1], min_val[l][m-1]})
          for (int vr : {max_val[m][r], min_val[m][r]}) {
            int v = get_val(op[m-1], vl, vr);
            max_val[l][r] = max(max_val[l][r], v);
            min_val[l][r] = min(min_val[l][r], v);
          }
      }
    }
  }

  cout << max_val[0][n - 1] << '\n';

  return 0;
}
