#include <bits/stdc++.h>
using namespace std;

bool query(int a, int b) {
  string s;
  cout << "? " << a << ' ' << b << endl;
  cin >> s;
  return s == "YES";
}

int main() {

  int n;
  cin >> n;

  vector<int> a(n);
  iota(begin(a), end(a), 1);
  ranges::stable_sort(a, query);

  vector<int> b(n);
  for (int i = 0; i < n; ++i)
    b[a[i] - 1] = i + 1;

  cout << "!";
  for (int i : b) cout << ' ' << i;
  cout << endl;

  return 0;
}
