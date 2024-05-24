#include <cstdio>
#include <cstdint>
#include <algorithm>

const int kN = 9000000;
struct Val {
  uint8_t v[3];
  void set(int u) { v[0] = u >> 16; v[1] = (u >> 8) & 255; v[2] = u & 255; }
  inline int get() const { return (1 << 16) * v[0] + (1 << 8) * v[1] + v[2]; }
  bool operator < (const Val& o) const { return get() < o.get(); }
};

Val a[kN];

int main() {
  int T;
  scanf("%d", &T);

  while (T --> 0) {
    int N, A, B, M, D0, K;
    scanf("%d%d%d%d%d%d", &N, &A, &B, &M, &D0, &K);

    for (int i = 0, v = D0; i < N; ++i) {
      a[i].set(v);
      v = (int) (((int64_t) v * A + B) % M);
    }

    std::sort(a, a + N);

    for (int i = 0; i < K; ++i) printf("%d%c", a[i].get(), " \n"[i + 1 == K]);
    for (int i = (N - K) / 2; i < (N + K) / 2; ++i) printf("%d%c", a[i].get(), " \n"[i + 1 == (N + K) / 2]);
    for (int i = N - K; i < N; ++i) printf("%d%c", a[i].get(), " \n"[i + 1 == N]);
  }

  return 0;
}
