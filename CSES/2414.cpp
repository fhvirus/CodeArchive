#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

vi recover(const vi& A, int a) {
  multiset<int> ms;
  for (int i : A) ms.insert(i);
  vi res(1, a);
  while (not ms.empty()) {
    int v = *begin(ms) - res[0];
    for (int i : res) {
      auto it = ms.find(i + v);
      if (it == end(ms)) return {};
      ms.erase(it);
    }
    res.push_back(v);
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  const int m = n * (n - 1) / 2;

  vi A(m);
  for (int &i : A) cin >> i;
  sort(all(A));

  for (int i = 2; i <= n; ++i) {
    int a = (A[0] + A[1] - A[i]);
    if (a % 2) continue;
    a /= 2;
    vi res = recover(A, a);
    if (res.empty()) continue;
    rep (j, 0, n) cout << res[j] << " \n"[j == n - 1];
    exit(0);
  }

  assert(0);

  return 0;
}
