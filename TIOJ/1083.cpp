#include <cstdio>
#include <string>

int main() {
  const int kN = 43;
  std::string seq[kN];
  seq[0] = "";
  seq[1] = "1";
  for (int i = 2; i < kN; ++i) {
    auto &s = seq[i - 1], &t = seq[i];
    for (int j = 0, k = 0; j < (int) s.size(); j = k) {
      while (s[j] == s[k]) ++k;
      t += std::to_string(k - j) + s[j];
    }
  }

  int n;
  while (scanf("%d", &n), n != 0)
    printf("%d %6lf\n", (int) seq[n].size(), (double) seq[n - 1].size() / (double) seq[n].size());
}
