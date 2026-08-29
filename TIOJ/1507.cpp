#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  boost::multiprecision::cpp_int a, b;
  char type;
  cin >> a >> type >> b;

  if (type == '*') cout << a * b << '\n';
  else cout << a / b << '\n';

  return 0;
}
