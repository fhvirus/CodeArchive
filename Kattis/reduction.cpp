#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  scanf("%d", &T);

  for (int t = 1; t <= T; ++t) {
    printf("Case %d\n", t);

    int N, M, L;
    cin >> N >> M >> L;

    char buf[20];
    int A, B;

    vector<pair<int, string>> agencies;
    for (int i = 0; i < L; ++i) {
      scanf(" %[^:]:%d,%d", buf, &A, &B);
      int ans = 0, cur = N;
      while (cur / 2 >= M and (cur - cur / 2) * A >= B)
        ans += B, cur /= 2;
      agencies.emplace_back(ans + (cur - M) * A, buf);
    }

    ranges::sort(agencies);
    for (auto [cost, name] : agencies)
      printf("%s %d\n", name.c_str(), cost);
  }

  return 0;
}
