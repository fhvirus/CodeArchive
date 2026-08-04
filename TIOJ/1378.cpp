#include <cstdio>

const int kN = 505;
char s[kN], stk[kN];

int pri(char c) {
  return c == '*' or c == '/' ? 2 : (
      c == '+' or c == '-' ? 1 : 0);
}

int main() {
  scanf("%s", s);

  int top = 0;
  for (int i = 0; s[i] != '\0'; ++i) {
    char c = s[i];
    if (c == '(') stk[++top] = c;
    else if (c == ')') {
      while (stk[top] != '(')
        putchar(stk[top--]);
      --top;
    } else if (pri(c) != 0) {
      while (top > 0 and pri(stk[top]) >= pri(c))
        putchar(stk[top--]);
      stk[++top] = c;
    } else putchar(c);
  }

  while (top > 0) putchar(stk[top--]);
  putchar('\n');

  return 0;
}
