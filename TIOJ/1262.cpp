#ifdef OWO
#include <bits/stdc++.h>
using namespace std;
string ans;
void Initialize() { cin >> ans; }
int Guess(const char s[], int len)
{ return ans.find(string(s, s + len)) != string::npos; }
void Report(const char s[])
{ puts(s); }
#else
#include "lib1262.h"
#endif

int main() {
  Initialize();

  char s[200];
  int l = 1, r = 1;

  for (bool can = true; can; ++r) {
    can = false;
    for (int i = 'a'; i <= 'z'; ++i) {
      s[100 + r - 1] = char(i);
      if (Guess(s + 100, r)) {
        can = true;
        break;
      }
    }
  }
  r -= 2;

  for (bool can = true; can; ++l) {
    can = false;
    for (int i = 'a'; i <= 'z'; ++i) {
      s[100 - l] = char(i);
      if (Guess(s + 100 - l, l + r)) {
        can = true;
        break;
      }
    }
  }
  l -= 2;

  s[100 + r] = '\0';

  Report(s + 100 - l);

  return 0;
}
