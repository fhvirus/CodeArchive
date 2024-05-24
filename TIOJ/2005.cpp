#include <cstdio>
#include <algorithm>
#include <array>

int main() {
  int N, M;

  typedef std::array<std::array<int, 3>, 3> Mat3;
  Mat3 r, x, t;
  auto mul = [&](Mat3 &a, Mat3 &b, Mat3 &c) -> void {
    for (int u : {0, 1, 2}) for (int v : {0, 1, 2})
      t[u][v] = (a[u][0] * b[0][v] + a[u][1] * b[1][v] + a[u][2] * b[2][v]) % M;
    c = t;
  };

  while (scanf("%d%d", &N, &M) != EOF) {
    int ans = 0;
    for (int i = 1, j = 10; i <= N; i *= 10, j = j * 10 % M) {
      x[0] = {j, 1, 1}; r[0] = {1, 0, 0};
      x[1] = {0, 1, 1}; r[1] = {0, 1, 0};
      x[2] = {0, 0, 1}; r[2] = {0, 0, 1};
      int e = std::min(N, i * 10 - 1) - i + 1;
      for (; e; e >>= 1, mul(x, x, x))
        if (e & 1) mul(r, x, r);
      ans = (ans * r[0][0] + (i - 1) % M * r[0][1] + r[0][2]) % M;
    }
    printf("%d\n", ans);
  }
}
