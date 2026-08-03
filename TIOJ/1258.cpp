#include <bits/stdc++.h>
using namespace std;

const int64_t A000170[] = {1, 1, 0, 0, 2, 10, 4, 40, 92,
  352, 724, 2680, 14200, 73712, 365596, 2279184, 14772512,
  95815104, 666090624, 4968057848l, 39029188884l, 314666222712l,
  2691008701644l, 24233937684440l, 227514171973736l, 2207893435808352l};

bool dfs(int i, int n, int dl, int d, int dr,
    auto& pos, auto& ul, auto& u, auto& ur) {
  if (i == n) return true;
  if (pos[i] != -1) {
    int j = (1 << pos[i]);
    return dfs(i + 1, n, (dl | j) << 1, d | j, (dr | j) >> 1, pos, ul, u, ur);
  }
  int no = dl | d | dr | ul[i] | u[i] | ur[i];
  for (int p = (((1 << n) - 1) & ~no), j = p & -p;
      p != 0; p ^= j, j = p & -p) {
    pos[i] = __lg(j);
    if (dfs(i + 1, n, (dl | j) << 1, d | j, (dr | j) >> 1, pos, ul, u, ur))
      return true;
    pos[i] = -1;
  }
  return false;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (string in; getline(cin, in); ) {
    if (in[0] == 'c') break;
    if (in[0] != 'a' and in[0] != 'b') continue;
    if (in[0] == 'a') {
      int N = stoi(in.substr(2));
      cout << A000170[N] % 124793 << endl;
      continue;
    }
    stringstream ss(in.substr(2));
    int N, M;
    ss >> N >> M;
    vector<int> pos(N, -1), ul(N), u(N), ur(N);
    for (int x, y, i = 0; i < M; ++i) {
      ss >> x >> y; x -= 1, y -= 1;
      pos[x] = y;
      ul[x] |= (1 << y);
      u[x] |= (1 << y);
      ur[x] |= (1 << y);
    }
    for (int j = N - 1; j > 0; --j) {
      ul[j - 1] |= ul[j] << 1;
      u[j - 1] |= u[j];
      ur[j - 1] |= ur[j] >> 1;
    }
    dfs(0, N, 0, 0, 0, pos, ul, u, ur);
    for (int i = 0; i < N; ++i)
      cout << pos[i] + 1 << " \n"[i == N - 1];
  }

  return 0;
}
