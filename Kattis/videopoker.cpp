#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;

constexpr ull get_card(const char n, const char s) {
  ull res = (isdigit(n) ? n - '2' : string("TJQKA").find(n) + 8) * 4;
  res += string("cdhs").find(s);
  return 1ull << res;
}
constexpr ull get_hand(const string& s) {
  ull res = 0;
  for (int i = 0; i < 5; ++i)
    res |= get_card(s[i * 3], s[i * 3 + 1]);
  return res;
}
constexpr ull kRoyal = get_hand("As Ks Qs Js Ts");
constexpr ull kWheel = get_hand("As 2s 3s 4s 5s");
const     ull kFlush = 0x8888888888888ull;
inline bool is_subset(ull a, ull b) { return (a & b) == a; }

int C(int a, int b) {
  if (0 > b or b > a) return 0;
  int res = 1;
  for (int i = 1; i <= b; ++i)
    res = res * (a - i + 1) / i;
  return res;
}

void solve(int i, int j, vector<int>& left, vector<int>& has, int comb, vector<int>& res) {
  if (i == 5) {
    array<int, 5> cnt {0};
    for (int i : has) cnt[i] += 1;
    if (cnt[4]) res[6] += comb; // four o.a.k
    else if (cnt[3]) res[cnt[2] ? 5 : 2] += comb; // full house, three o.a.k
    else if (cnt[2]) res[cnt[2] == 2] += comb;    // two / one pair
    else {
      int len = 0, cur = 0;
      for (int i : has) {
        cur = (i ? cur + 1 : 0);
        len = max(len, cur);
      }
      if (len == 5 or (has[0] and has[1] and has[2] and has[3] and has.back())) res[3] += comb;
    }
    return;
  }
  if (j == 13) return;
  for (; j < 13; ++j) for (int k = 1; i + k <= 5 and k <= left[j]; ++k) {
    left[j] -= k, has[j] += k;
    solve(i + k, j + 1, left, has, comb * C(left[j] + k, k), res);
    left[j] += k, has[j] -= k;
  }
}

vector<int> solve(ull h, ull hand) {
  int n = popcount(h);
  vector<int> res(9);
  ull deck = (1ull << 52) - 1 - hand;

  // royal flush & straight flush
  for (int i = 0; i < 36; ++i)
    res[i < 4 ? 8 : 7] += is_subset((kRoyal >> i), (h | deck)) and
                          is_subset(h, (kRoyal >> i));
  for (int i = 0; i < 4; ++i)
    res[7] += is_subset((kWheel >> i), (h | deck)) and
              is_subset(h, (kWheel >> i));

  // flush
  for (int i = 0; i < 4; ++i)
    res[4] += is_subset(h, (kFlush >> i)) *
      C(popcount((kFlush >> i) & deck), 5 - n);

  // dedup straight & flush
  res[4] -= res[7] + res[8];
  res[3] -= res[7] + res[8];

  vector<int> left(13), has(13);
  for (int i = 0; i < 13; ++i) {
    left[i] = 4 - popcount((hand >> (i * 4)) & 0xf);
    has[i] = popcount((h >> (i * 4)) & 0xf);
  }

  solve(n, 0, left, has, 1, res);

  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  cout << setprecision(7) << fixed;

  vector<int> x(9);
  for (int &i : x) cin >> i;
  const auto get_score = [&x](const vector<int>& cnt, const int n) -> double {
    return double(inner_product(begin(x), end(x), begin(cnt), 0)) / C(47, 5 - n);
  };

  int n;
  cin >> n >> ws;
  for (string s; n --> 0; ) {
    getline(cin, s);
    auto hand = get_hand(s);
    double ans = get_score(solve(0, hand), 0);
    for (ull h = hand; h; h = ((h - 1) & hand))
      ans = max(ans, get_score(solve(h, hand), popcount(h)));
    cout << ans << '\n';
  }

  return 0;
}

