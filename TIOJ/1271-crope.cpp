#include "lib1271.h"
#include <ext/rope>

__gnu_cxx::crope s[1'000'001];
int n;

void Init() {
  while (n > 0) s[n--].clear();
  s[0] = "";
}
void TypeLetter(char c) {
  s[n + 1] = s[n];
  n += 1;
  s[n].push_back(c);
}
void UndoCommands(int k) {
  s[n + 1] = s[n - k];
  n += 1;
}
char GetLetter(int p) { return s[n][p]; }
