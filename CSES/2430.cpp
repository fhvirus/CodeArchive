#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int cnt(int a, int b) {
  int res = 0;
  if (a < b) swap(a, b);
  while (a != b) {
    int t = a / (b + 1);
    res += t;
    a -= (b + 1) * t;
    swap(a, b);
  }
  return (a == 0 ? res : INT_MAX);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  pii sol(n, n);
  rep (i, 0, n) {
    pii cur(cnt(i, n - i), i);
    sol = min(sol, cur);
  }

  int t = 0, a = sol.second, b = n - a;
  rep (i, 0, sol.first) {
    if (a < b) swap(a, b), t ^= 1;
    cout << t;
    a -= (b + 1);
  }
  cout << '\n';

  return 0;
}
