#include <bits/stdc++.h>
using namespace std;

bool query(int x) {
  string s;
  cout << "? " << x << endl;
  cin >> s;
  return s == "YES";
}

int main() {
  const int kC = 1e9;

  int ans = 0;
  for (int l = (1 << __lg(kC)); l > 0; l /= 2) {
    if (ans + l < kC and query(ans + l))
      ans += l;
  }
  
  cout << "! " << ans + 1 << endl;

  return 0;
}
