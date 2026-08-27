#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<string> name(1, "");
  vector<int> par(1, 0), len(1, 0), stk(1, 0);
  for (string s; getline(cin, s); ) {
    name.push_back(s);
    auto p = s.find_last_of(':');
    len.emplace_back(size(s) - (p == string::npos ? 0 : p + 1));
    const auto par_name = (p == string::npos ? ""s : s.substr(0, p));
    while (name[stk.back()] != par_name) stk.pop_back();
    par.push_back(stk.back());
    stk.push_back((int)size(par) - 1);
  }

  int n = (int)size(name);
  vector<int> shift(n);
  vector<deque<pair<int, int>>> width(n);

  for (int i = n - 1; i > 0; --i) {
    auto &w = width[i], &pw = width[par[i]];
    if (empty(w)) w.emplace_back(0, len[i] - 1);
    else {
      auto [Ls, Le] = w[0];
      int L = len[i], Lc = Le - Ls + 1; // TODO: or all sub nodes?
      int left_len = (L >= Lc ? -1 * ((L - Lc) / 2) : (Lc - L) / 2);
      int S = Ls + left_len;
      w.emplace_front(S, S + L - 1);
    }
    shift[i] = (empty(pw) ? 0 : INT_MAX);
    for (size_t j = 0; j < min(size(w), size(pw)); ++j)
      shift[i] = min(shift[i], pw[j].first - 2 - w[j].second);
    for (size_t j = 0; j < size(w); ++j) {
      auto [lb, rb] = w[j];
      if (j < size(pw)) pw[j].first = lb + shift[i];
      else pw.emplace_back(lb + shift[i], rb + shift[i]);
    }
  }

  vector<int> pos(n), dep(n);
  for (int i = 1; i < n; ++i) {
    shift[i] += shift[par[i]];
    pos[i] = width[i][0].first + shift[i];
    dep[i] = dep[par[i]] + 3;
  }

  int lb = *ranges::min_element(pos);
  for (int i = 1; i < n; ++i)
    cout << name[i] << " (" << pos[i]-lb+1 << ',' << dep[i] << ")\n";

  return 0;
}
