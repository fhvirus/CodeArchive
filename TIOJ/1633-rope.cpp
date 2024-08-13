#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M;
  cin >> N >> M;

  __gnu_cxx::rope<int> r;
  rep (i, 0, N) r.push_back(i + 1);
  rep (i, 0, N) r.push_back(N - i);

  auto swap_r = [&r](int a, int b, int c, int d) -> void {
    auto u = r.substr(a, b - a);
    auto v = r.substr(c, d - c);
    r.erase(c, d - c);
    r.erase(a, b - a);
    r.insert(a, v);
    r.insert(d - (b - a), u);
  };

  rep (_, 0, M) {
    string s;
    cin >> s;
    if (s == "REV") {
      int a, b;
      cin >> a >> b;
      --a;
      swap_r(a, b, 2 * N - b, 2 * N - a);
    } else {
      int a, b, c, d;
      cin >> a >> b >> c >> d;
      --a; --c;
      swap_r(a, b, c, d);
      swap_r(2 * N - d, 2 * N - c, 2 * N - b, 2 * N - a);
    }
  }

  rep (i, 0, N)
    cout << r[i] << " \n"[i == N - 1];

  return 0;
}
