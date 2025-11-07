#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

bool is_solved(const string& s) {
  static regex solved("[A\\.]+[B\\.]+");
  return regex_match(s, solved);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  string s;
  cin >> s;

  // cannot change letter order if n <= 2
  if (n <= 2) {
    cout << (is_solved(s) ? 0 : -1) << '\n';
    exit(0);
  }

  vector<string> sol;
  const auto op = [&](int i, int j) {
    swap(s[i], s[j]); swap(s[i + 1], s[j + 1]);
    sol.push_back(s);
  };

  const int e = 2 * n - 2;
  if ((int) s.find("..") == e - 1) op(0, e - 1);
  if ((int) s.find("..") != e) op((int) s.find(".."), e);

  // the two only unsolvable case for n = 3
  if (n == 3 and (s == "ABAB.." or s == "BABA..")) {
    cout << -1 << '\n';
    exit(0);
  }

  // solvable for all n > 3
  while (not is_solved(s)) {
    int b = (int) s.find('B');
    if (s.find('A', b + 2) == string::npos) { // A...ABAB...B..
      op(b + 2, e);
      op(b, b + 2);
      op(b + 3, b);
      assert(is_solved(s));
      break;
    }
    int a = (int) s.find('A', b + 2);
    op(b, e);
    op(a, b);
    if (a == e - 1) {
      if (n > 3) {
        op(b + 1, e - 1);
        op(e, b + 1);
      }
    } else op(e, a);
  }

  cout << sz(sol) << '\n';
  for (string i : sol)
    cout << i << '\n';

  return 0;
}
