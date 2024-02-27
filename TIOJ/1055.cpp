#include <cstdio>

int main(){
  int a, b;
  scanf("%d%d", &a, &b);
  b += (a < b ? 1 : -1);
  for (int i = a; i != b; i += (a < b ? 1 : -1)) {
    for (int j = 0; j <= i; ++j)
      putchar("*\n"[j == i]);
  }
  return 0;
}
