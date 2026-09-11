#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  
  string pat; cin >> pat;
  pat = regex_replace(pat, regex("\\."), "\\.");
  pat = regex_replace(pat, regex("\\$+"), ".*");
  regex r(pat);

  for (string s; cin >> s; )
    if (regex_match(s, r)) cout << s << '\n';

  return 0;
}
