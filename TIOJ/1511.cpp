#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (uint64_t n; cin >> n >> ws; ) {
    string s; getline(cin, s);
    uint64_t right = (n % 2 == 0 ? n * (n / 2 - 1) : 0);
    uint64_t obtuse = ((n - 1) / 2) * ((n - 1) / 2 - 1) / 2 * n;
    uint64_t acute = n * (n - 1) / 2 * (n - 2) / 3 - right - obtuse;
    cout << (s[0] == 'R' ? right : (s[0] == 'O' ? obtuse : acute)) << '\n';
  }

  return 0;
}
