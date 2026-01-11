#include <bits/stdc++.h>
using namespace std;

int main() {

  int n;
  cin >> n;

  vector<int> a(n);
  for (int l = __lg(n); l >= 0; --l) {
    string s(n, '0');
    for (int i = 0; i < n; ++i) s[i] |= (i >> l & 1);
    cout << "? " << s << endl;
    cin >> s;
    for (int i = 0; i < n; ++i) a[i] |= ((s[i] - '0') << l);
  }

  cout << '!';
  for (int i : a) cout << ' ' << i + 1;
  cout << endl;

  return 0;
}
