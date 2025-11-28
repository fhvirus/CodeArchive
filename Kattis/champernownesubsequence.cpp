#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  string s;
  cin >> s;

  queue<char> q;
  int p = 0;

  for (char c : s) {
    while (q.empty() or q.front() != c) {
      if (q.empty()) {
        p += 1;
        string t;
        for (int u = p; u > 0; u /= 10)
          t.push_back(char('0' + u % 10));
        while (not t.empty()) {
          q.push(t.back());
          t.pop_back();
        }
      } else q.pop();
    }
    q.pop();
  }

  cout << p << '\n';

  return 0;
}

