#include <cstdio>
#include <cstring>

int main() {
  char s[33];

  while (scanf("%s", s) != EOF) {
    bool ans = true;
    for (int i = 0, j = (int) strlen(s) - 1; i < j; ++i, --j)
      ans &= (s[i] == s[j]);
    puts(ans ? "palindrome" : "not palindrome");
  }

  return 0;
}
