#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, Q;
  cin >> N >> Q;

  vector<int> a(N + 2);
  a[0] = INT_MAX;
  a[N + 1] = INT_MIN;
  for (int i = 1; i <= N; ++i)
    cin >> a[i];

  set<int> right_end;
  map<int, int> len_count;
  for (int i = 0; i <= N; ++i) if (a[i] > a[i + 1]) {
    auto it = right_end.insert(i).first;
    if (it != begin(right_end))
      len_count[i - *prev(it)] += 1;
  }

  auto remove_count = [&](int l) -> void {
    len_count[l] -= 1;
    if (len_count[l] == 0)
      len_count.erase(l);
  };
  auto remove_end = [&](int p) -> void {
    auto it = right_end.lower_bound(p);
    if (it != begin(right_end)) remove_count(p - *prev(it));
    if (next(it) != end(right_end)) remove_count(*next(it) - p);
    if (it != begin(right_end) and next(it) != end(right_end))
      len_count[*next(it) - *prev(it)] += 1;
    right_end.erase(it);
  };
  auto insert_end = [&](int p) -> void {
    auto it = right_end.insert(p).first;
    if (it != begin(right_end) and next(it) != end(right_end))
      remove_count(*next(it) - *prev(it));
    if (it != begin(right_end)) len_count[p - *prev(it)] += 1;
    if (next(it) != end(right_end)) len_count[*next(it) - p] += 1;
  };

  for (int cmd, p, x, b, i = 0; i < Q; ++i) {
    cin >> cmd;
    if (cmd == 1) {
      cin >> p >> x;
      if (a[p - 1] > a[p]) remove_end(p - 1);
      if (a[p] > a[p + 1]) remove_end(p);
      a[p] = x;
      if (a[p - 1] > a[p]) insert_end(p - 1);
      if (a[p] > a[p + 1]) insert_end(p);
    } else {
      cin >> b;
      auto it = prev(end(len_count));
      if (b == 0) cout << it->first << '\n';
      else if (b == 1) {
        if ((int) len_count.size() == 1) cout << 0 << '\n';
        else cout << prev(it)->first << '\n';
      } else {
        if (it->second > 1) cout << it->first << '\n';
        else {
          if ((int) len_count.size() == 1) cout << 0 << '\n';
          else cout << prev(it)->first << '\n';
        }
      }
    }
  }

  return 0;
}
