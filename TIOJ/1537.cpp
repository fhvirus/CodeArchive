#include <bits/stdc++.h>
using namespace std;

void dfs(int L, auto& stk) {
  if (L == 0) {
    for (size_t i = 0; i < size(stk); ++i)
      cout << stk[i] << (i == size(stk) - 1 ? "\n" : ", ");
    return;
  }
  int last = (empty(stk) ? 0 : stk.back());
  for (int i = max(last, 1); i <= L - (last == 0); ++i) {
    stk.push_back(i);
    dfs(L - i, stk);
    stk.pop_back();
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, L;
  cin >> N;
  
  for (int t = 1; t <= N; ++t) {
    cout << "Plank " << t << ":\n";
    cin >> L;
    vector<int> stk;
    dfs(L, stk);
  }

  return 0;
}
