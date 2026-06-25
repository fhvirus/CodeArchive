// Ref: https://github.com/jeremykvlim/kattis/blob/main/open/towers.cpp

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-12;
bool compare(vector<int> a, vector<int> b) {
  a.erase(ranges::find(a, 1), end(a));
  b.erase(ranges::find(b, 1), end(b));
  if (a == b) return false;

  double ratio = 1, val_a = 1;
  for (int h = (int) max(size(a), size(b)); h >= 0; --h) {
    double x = (h < (int) size(a) ? a[h] : 1);
    double y = (h < (int) size(b) ? b[h] : 1);
    double log_r = ratio * log(y) - log(x);

    if (abs(log_r) > log(7)) return log_r > 0;

    ratio = (abs(log_r) < EPS ? 1 : exp(val_a * log_r));
    val_a = pow(x, val_a);
  }

  return ratio > 1;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int M;
  cin >> M;

  vector<vector<int>> towers(M);

  for (auto &t : towers) {
    string s, tmp;
    cin >> s;
    istringstream is(s);
    while (getline(is, tmp, '^')) t.push_back(stoi(tmp));
  }

  stable_sort(begin(towers), end(towers), compare);

  cout << "Case 1:\n";
  for (auto &t : towers)
    for (size_t i = 0; i < size(t); ++i)
      cout << t[i] << "^\n"[i + 1 == size(t)];

  return 0;
}
