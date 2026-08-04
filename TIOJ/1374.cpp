#include <bits/stdc++.h>
using namespace std;

const string t = "BlackToAttack";
void NO() { cout << "NO\n0\n"; exit(0); }

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string s;
  cin >> s;

  auto pos_l = s.find('l');
  if (pos_l == string::npos) NO();

  const auto prv = [&](auto i) { return i == 0 ? size(s) - 1 : i - 1; };

  int Bs = 0;
  for (auto i = prv(pos_l); s[i] == 'B'; i = prv(i)) Bs += 1;
  if (Bs == 0 or (Bs == 1 and s != t)) NO();

  string noB;
  for (char c : s) if (c != 'B') noB.push_back(c);
  ranges::rotate(noB, begin(noB) + noB.find('l'));
  if (noB != t.substr(1)) NO();

  cout << "YES\n" << ranges::count(s, 'B') - 1 << '\n';

  return 0;
}
