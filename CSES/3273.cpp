#include <bits/stdc++.h>
using namespace std;

bool query(int i) {
  char c;
  cout << "? " << i << endl;
  cin >> c;
  return c == 'B';
}
void answer(int i) { cout << "! " << i << endl; exit(0); }

int main() {

  int n;
  cin >> n;

  int f = query(1);
  if (query(n) == f) answer(n);

  int p = 1;
  for (int l = (1 << __lg(n)); l > 0; l /= 2) {
    int t = p + l;
    if (p + l >= n) continue;
    int v = query(t);
    if ((f ^ 1) == (v ^ (t & 1))) p = t;
  }

  answer(p);

  return 0;
}
