#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int L, N, M;
  cin >> L >> N >> M;

  vector<int> key(N);
  for (int &i : key) cin >> i;

  string t(N, ' ');
  for (string s; L --> 0; ) {
    cin >> s;
    for (int i = 0; i < M; ++i) {
      for (int j = 0; j < N; ++j)
        t[key[j] - 1] = s[j];
      t.swap(s);
    }
    cout << s << '\n';
  }

  return 0;
}
