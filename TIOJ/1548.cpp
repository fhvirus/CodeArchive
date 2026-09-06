#include <bits/stdc++.h>
using namespace std;

const unordered_map<string, int> day2num = {
  {"Sunday", 0}, {"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3},
  {"Thursday", 4}, {"Friday", 5}, {"Saturday", 6},
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m, q;
  cin >> n >> m >> q;

  vector<string> name(n);
  for (auto &i : name) cin >> i;
  ranges::sort(name);

  vector claim(size(name), vector<pair<int, int>>());
  cin >> ws;
  for (int i = 0; i < q; ++i) {
    string s; getline(cin, s);
    auto p = s.find(':');
    auto who = s.substr(0, p), what = s.substr(p + 2);
    auto id = ranges::lower_bound(name, who) - begin(name);
    if (what == "I am evil.") claim[id].emplace_back(id, 1);
    else if (what == "I am not evil.") claim[id].emplace_back(id, 0);
    else if (what.substr(0, 9) == "Today is " and what.back() == '.') {
      auto day = what.substr(9, size(what) - 10);
      if (day2num.count(day)) claim[id].emplace_back(-1, day2num.at(day));
    } else {
      p = what.find(' ');
      if (p == string::npos) continue;
      auto whom = what.substr(0, p);
      what = what.substr(p + 1);
      auto to = ranges::lower_bound(name, whom) - begin(name);
      if (name[to] != whom) continue;
      if (what == "is evil.") claim[id].emplace_back(to, 1);
      else if (what == "is not evil.") claim[id].emplace_back(to, 0);
    }
  }

  int maybe_fan = 0;
  for (int fan = 0; fan < n; ++fan) for (int day = 0; day < 7; ++day) {
    int liar = 0, unknown = 0, good = true;
    for (int i = 0; i < n; ++i) {
      int truth = 0, lie = 0;
      for (auto [id, what] : claim[i]) {
        bool is_truth = (id == -1 ? (what == day) : (fan == id) == (what == 1));
        (is_truth ? truth : lie) += 1;
      }
      if (truth > 0 and lie > 0) { good = false; break; }
      liar += (lie > 0);
      unknown += (truth == 0 and lie == 0);
    }
    good &= (liar <= m and m <= liar + unknown);
    if (good) maybe_fan |= (1 << fan);
  }

  int cnt_fan = popcount((unsigned)maybe_fan);
  if (cnt_fan == 0) cout << "Impossible\n";
  else if (cnt_fan > 1) cout << "Cannot Determine\n";
  else cout << name[__lg(maybe_fan)] << '\n';

  return 0;
}
