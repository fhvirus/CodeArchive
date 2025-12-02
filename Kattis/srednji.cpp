#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, B;
  cin >> N >> B;

  vector<int> A(N);
  for (int &i : A) cin >> i;

  int p = (int) (find(begin(A), end(A), B) - begin(A));
  map<int, int> cnt;
  int cur = 0, ans = 0;
  for (int i = p; i < N; ++i) {
    cur += (A[i] > B) - (A[i] < B);
    cnt[cur] += 1;
  }
  cur = 0;
  for (int i = p; i >= 0; --i) {
    cur -= (A[i] > B) - (A[i] < B);
    if (cnt.count(cur)) ans += cnt.at(cur);
  }

  cout << ans << '\n';

  return 0;
}
