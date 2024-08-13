#include <cstdio>

int a[10][10] = {
   4,  3,  2,  1, 66, 67, 70, 71, 74, 75,
   5,  6,  7,  8, 65, 68, 69, 72, 73, 76,
  12, 11, 10,  9, 64, 63, 62, 79, 78, 77,
  13, 14, 15, 16, 59, 60, 61, 80, 81, 82,
  20, 19, 18, 17, 58, 57, 56, 85, 84, 83,
  21, 22, 23, 24, 53, 54, 55, 86, 87, 88,
  28, 27, 26, 25, 52, 51, 50, 91, 90, 89,
  29, 30, 37, 38, 47, 48, 49, 92, 93, 94,
  32, 31, 36, 39, 46, 45, 44, 97, 96, 95,
  33, 34, 35, 40, 41, 42, 43, 98, 99,100,
};

typedef unsigned long long ull;
ull b[10][10];
ull count() {
  for (int i = 0; i < 10; ++i) for (int j = 0; j < 10; ++j) b[i][j] = (a[i][j] == 1);
  for (int v = 1; v <= 100; ++v) {
    for (int i = 0; i < 10; ++i) for (int j = 0; j < 10; ++j) if (a[i][j] == v) {
      if (i > 0 and a[i - 1][j] > v) b[i - 1][j] += b[i][j];
      if (i < 9 and a[i + 1][j] > v) b[i + 1][j] += b[i][j];
      if (j > 0 and a[i][j - 1] > v) b[i][j - 1] += b[i][j];
      if (j < 9 and a[i][j + 1] > v) b[i][j + 1] += b[i][j];
      if (v == 100) return b[i][j];
    }
  }
  return 0;
}

int main() {

  // printf("Needs: 64215391721\n");
  // printf("Count: %llu\n", count());

  puts("10");
  for (int i = 0; i < 10; ++i)
    for (int j = 0; j < 10; ++j)
      printf("%d%c", a[i][j], " \n"[j + 1 == 10]);

  return 0;
}
