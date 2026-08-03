// assume characters will always be the same
#include <bits/stdc++.h>
using namespace std;

const int diff[9] = {0, 1, -1, 1, 1, 0, -1, -1, 0};
const map<int, char> ans = {
  { 4, '.'}, {10, '-'}, {12, '='}, {29, 'y'},
  {18, '1'}, {30, '2'}, {34, '3'}, {32, '4'},
  {31, '5'}, {27, '6'}, {21, '7'}, {35, '8'} };

char titta(auto& t, int si, int sj, bool flag = true) {
  int n = (int)size(t), m = (int)size(t[0]);
  int sz = 0, max_i = si, min_i = si, max_d = 0;
  queue<pair<int, int>> q;
  t[si][sj] = '.', q.emplace(si, sj);
  while (not empty(q)) {
    auto [i, j] = q.front(); q.pop();
    sz += 1, max_i = max(max_i, i), min_i = min(min_i, i);
    int deg = (i != si or j != sj);
    for (int d = 0; d < 8; ++d) {
      int ni = i + diff[d], nj = j + diff[d + 1];
      if (0 <= ni and ni < n and 0 <= nj and nj < m and t[ni][nj] == '*')
        t[ni][nj] = '.', q.emplace(ni, nj), ++deg;
    }
    max_d = max(max_d, deg);
  }
  if (sz == 12 and flag) titta(t, si + 4, sj, false);
  if (sz == 19) return "()"[max_i - si == 18];
  if (sz == 24) return "+x"[max_i - min_i == 7];
  if (sz == 26) return "90"[max_d == 2];
  return ans.at(sz);
}

void solve(auto& t) {
  int n = (int)size(t), m = (int)size(t[0]);
  for (int j = 0; j < m; ++j) {
    int pos = -1;
    for (int i = 0; i < n; ++i)
      if (t[i][j] == '*') { pos = i; break; }
    if (pos != -1) cout << titta(t, pos, j);
  }
  cout << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<string> t;
  for (string s; cin >> s; ) {
    if (s[0] == '-') {
      solve(t);
      t.clear();
    } else t.push_back(s);
  }
  solve(t);

  return 0;
}
