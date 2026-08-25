#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 100000;
constexpr int kS = (int)ceil(sqrt(kN)), kB = (kN + kS - 1) / kS;
int N, Q, a[kN];

int rank_in_own_b[kN], ord_in_b[kB][kS];
int num_lt_rank_in_b[kN][kS + 1];
int pair_in_b[kB][kS + 1][kS + 1];
int b_to_pre_b_le_rank[kB][kB][kS + 1];
int num_pre_b_le_val[kB][kN + 1];

int get_rank_in_b(int b, int v) {
  return num_pre_b_le_val[b][v - 1] - 
    (b > 0 ? num_pre_b_le_val[b - 1][v - 1] : 0);
}
int hel_inne(int l, int r, int d, int u) {
  int ans = 0, bi = l / kS;
  int rank_d = get_rank_in_b(bi, d);
  for (int i = l; i <= r; ++i) if (d <= a[i] and a[i] <= u) {
    ans += (num_lt_rank_in_b[i][rank_in_own_b[i]] -
        num_lt_rank_in_b[i][rank_d]);
    if (l > bi * kS)
      ans -= (num_lt_rank_in_b[l - 1][rank_in_own_b[i]] -
          num_lt_rank_in_b[l - 1][rank_d]);
  }
  return ans;
}

int count_e2e(int lb, int l, int rb, int r, int d, int u) {
  int ans = 0, cnt_l = 0;
  for (int i = 0, j = 0, jr = min(kS, N - rb * kS); j < jr; ++j) {
    while (i < kS and a[ord_in_b[lb][i]] < a[ord_in_b[rb][j]]) {
      int id = ord_in_b[lb][i++];
      cnt_l += (l <= id and d <= a[id] and a[id] <= u);
    }
    int id = ord_in_b[rb][j];
    if (id <= r and d <= a[id] and a[id] <= u)
      ans += cnt_l;
  }
  return ans;
}

int count_pair_two(int lb, int l, int rb, int r) {
  int ans = 0, cnt_l = 0;
  for (int i = 0, j = 0, jr = min(kS, N - rb * kS); j < jr; ++j) {
    while (i < kS and a[ord_in_b[lb][i]] < a[ord_in_b[rb][j]])
      cnt_l += (ord_in_b[lb][i++] >= l);
    if (ord_in_b[rb][j] <= r)
      ans += cnt_l;
  }
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  cin >> N >> Q;
  for (int i = 0; i < N; ++i) cin >> a[i];

  // prep work
  for (int bi = 0, bl = 0; bl < N; ++bi, bl += kS) {
    int br = min(bl + kS, N);
    for (int i = bl; i < br; ++i) {
      int r = 0;
      for (int j = bl; j < br; ++j) r += (a[i] > a[j]);
      rank_in_own_b[i] = r, ord_in_b[bi][r] = i;

      if (i > bl) copy_n(num_lt_rank_in_b[i - 1], br - bl + 1, num_lt_rank_in_b[i]);
      for (int j = rank_in_own_b[i] + 1; j <= br - bl; ++j)
        num_lt_rank_in_b[i][j] += 1;
    }

    for (int d = br - bl - 2; d >= 0; --d) {
      for (int u = d + 1, tot = 0; u < br - bl; ++u) {
        tot += (ord_in_b[bi][d] < ord_in_b[bi][u]);
        pair_in_b[bi][d][u] = tot + pair_in_b[bi][d + 1][u];
      }
    }

    for (int bj = 0; bj < bi; ++bj) {
      for (int ri = 0, rj = 0, tot = 0; ri < br - bl; ++ri) {
        while (rj < kS and a[ord_in_b[bj][rj]] < a[ord_in_b[bi][ri]]) ++rj;
        b_to_pre_b_le_rank[bi][bj][ri] = (tot += rj);
        if (bj > 0)
          b_to_pre_b_le_rank[bi][bj][ri] += b_to_pre_b_le_rank[bi][bj - 1][ri];
      }
    }

    for (int i = 0; i < br; ++i)
      num_pre_b_le_val[bi][a[i]] += 1;
    for (int i = 1; i <= N; ++i)
      num_pre_b_le_val[bi][i] += num_pre_b_le_val[bi][i - 1];
  }

  for (int l, r, d, u; Q --> 0; ) {
    cin >> l >> r >> d >> u; l -= 1, r -= 1;

    int lb = l / kS, rb = r / kS;

    if (lb == rb) {
      cout << hel_inne(l, r, d, u) << '\n';
      continue;
    }

    // pairs in each end and across ends
    int64_t ans = hel_inne(l, lb * kS + kS - 1, d, u) + hel_inne(rb * kS, r, d, u);
    ans += count_e2e(lb, l, rb, r, d, u);

    // pairs in blocks
    for (int bi = lb + 1; bi < rb; ++bi) {
      int rank_d = get_rank_in_b(bi, d),
          rank_u = get_rank_in_b(bi, u + 1) - 1;
      // single block
      ans += pair_in_b[bi][rank_d][rank_u];

      // pairs between full blocks
      ans += (b_to_pre_b_le_rank[bi][bi - 1][rank_u] -
          b_to_pre_b_le_rank[bi][lb][rank_u]);
      if (rank_d > 0)
        ans -= (b_to_pre_b_le_rank[bi][bi - 1][rank_d - 1] -
          b_to_pre_b_le_rank[bi][lb][rank_d - 1]);
      ans -= (rank_u - rank_d + 1) *
        (num_pre_b_le_val[bi - 1][d - 1] -
         num_pre_b_le_val[lb][d - 1]);
    }

    // pairs across ends and blocks
    for (int i = l; i < lb * kS + kS; ++i)
      if (d <= a[i] and a[i] <= u)
        ans += (num_pre_b_le_val[rb - 1][u]
            - num_pre_b_le_val[lb][u]
            - num_pre_b_le_val[rb - 1][a[i]]
            + num_pre_b_le_val[lb][a[i]]);
    for (int i = rb * kS; i <= r; ++i)
      if (d <= a[i] and a[i] <= u)
        ans += (num_pre_b_le_val[rb - 1][a[i] - 1]
            - num_pre_b_le_val[lb][a[i] - 1]
            - num_pre_b_le_val[rb - 1][d - 1]
            + num_pre_b_le_val[lb][d - 1]);

    cout << ans << '\n';
  }

  return 0;
}
