#include <bits/stdc++.h>
using namespace std;

vector<int> z_value(const string& s) {
  int n = (int) s.size(), l = 0, r = 0;
  vector<int> z(n);
  for (int i = 1; i < n; ++i) {
    if (i < r) z[i] = min(r - i, z[i - l]);
    while (s[i + z[i]] == s[z[i]]) z[i] += 1;
    if (i + z[i] > r) l = i, r = i + z[i];
  }
  return z;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  string A, B;
  cin >> A >> B;

  vector<int> z = z_value(B + '$' + A + A);
  reverse(begin(A), end(A));
  reverse(begin(B), end(B));
  vector<int> zR = z_value(B + '$' + A + A);

  vector<int> ans;
  for (int i = 0; i < N; ++i) {
    int lcp = z[N + 1 + i], lcs = zR[N + 1 + (N - i)];
    if (lcp + lcs + 1 == N)
      ans.push_back(i);
  }

  if (ans.empty()) {
    cout << "NIE\n";
    exit(0);
  }

  cout << "TAK\n";
  for (int i : ans) cout << i << ' ';
  cout << '\n';
}
