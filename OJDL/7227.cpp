#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vector<int> V(N + 1);
  for (int i = 1; i <= N; ++i)
    cin >> V[i];

  map<int, int> mp;
  for (int i = 1; i <= N; ++i)
    mp[V[i] * 2] ^= i;

  for (int i = 1; i <= N; ++i)
    cout << (mp[V[i]] ^ (V[i] == 0 ? i : 0)) << " \n"[i == N];

  return 0;
}
