#include <bits/stdc++.h>
using namespace std;

// credit: LittleCube

inline int msb(uint64_t bits) { return 63 - countl_zero(bits); }

inline uint32_t find_remain(uint64_t bits, int k) {
  uint32_t result = 0;
  for (int _ = 0; _ < k; _++) {
    result = (result << 4) | (msb(bits) / 4);
    bits ^= (1ull << msb(bits));
  }
  return result;
}

const uint64_t m_suit = 0x1111111111111;
const uint64_t m_straight = 0x11111;
const uint64_t m_a2345 = 0x1000000001111;
const uint64_t m_rank = 0xf;

inline uint64_t remove_mask(int rank) { return ~(m_rank << (rank * 4)); }

unsigned evaluate(uint64_t cards) {
  uint32_t pairs = 0, flush = 0;
  int triple = -1, quad = -1, straight = -1, straight_flush = -1;

  uint64_t occ = 0;
  for (int i = 0; i < 4; i++) {
    uint64_t rank = m_suit & (cards >> i);
    occ |= rank;
    if (popcount(rank) >= 5) flush = find_remain(rank, 5);
  }

  if (popcount(occ & m_a2345) == 5) straight = 3;
  for (int s : {0, 1, 2, 3})
    if (popcount((cards >> s) & m_a2345) == 5)
      straight_flush = 3;

  for (int i = 0; i < 13; i++) {
    if (popcount(occ >> (i * 4) & m_straight) == 5)
      straight = i + 4;
    for (int s : {0, 1, 2, 3})
      if (popcount(cards >> (i * 4 + s) & m_straight) == 5)
        straight_flush = i + 4;

    int cnt = popcount((cards >> (i * 4)) & m_rank);
    if (cnt >= 2) pairs |= (1u << i);
    if (cnt >= 3) triple = max(triple, i);
    if (cnt >= 4) quad = i;
  }

  // Straight Flush: does not matter (one card determines all five)
  if (straight_flush >= 0)
    return (1u << 27) | straight_flush;
  // Quad: does matter, pick one high card
  if (quad >= 0)
    return (1u << 26) | ((quad + 2) << 4) | find_remain(cards & remove_mask(quad), 1);
  // Full House: does not matter
  if (triple >= 0 && popcount(pairs) >= 2) {
    int large_pair = msb(pairs ^ (1u << triple));
    return (1u << 25) | (triple << 4) | large_pair;
  }
  // Flush: does matter, stored in flush
  if (flush != 0) return (1u << 24) | flush;
  // Straight: does not matter
  if (straight >= 0) return (1u << 23) | straight;
  // Three of a kind: does matter, pick two
  if (triple >= 0) return (1u << 22) | (triple << 8) | find_remain(cards & remove_mask(triple), 2);
  // Two pair
  if (popcount(pairs) >= 2) {
    int p0 = msb(pairs);
    int p1 = msb(pairs ^ (1u << p0));
    return (1u << 21) | (p0 << 8) | (p1 << 4) | find_remain(cards & remove_mask(p0) & remove_mask(p1), 1);
  }
  // Pair
  if (pairs) return (1u << 20) | (msb(pairs) << 12) | find_remain(cards & remove_mask(msb(pairs)), 3);
  return find_remain(cards, 5);
}

const string suits = "cdhs";
const string ranks = "23456789TJQKA";
inline uint64_t get_id() {
  string card; cin >> card;
  return 1ull << (suits.find(card[0]) + 4 * ranks.find(card[1]));
}

void solve() {
  uint64_t hand = 0, op_hand = 0, table = 0;
  for (int _ : {0, 1}) hand |= get_id();
  for (int _ : {0, 1}) op_hand |= get_id();
  for (int _ : {0, 1, 2, 3}) table |= get_id();
  uint64_t deck = ((1ull << 52) - 1) ^ hand ^ op_hand ^ table;

  int win = 0, draw = 0, lose = 0;
  while (deck != 0) {
    uint64_t t = 1ull << msb(deck);
    auto a = evaluate(hand | table | t);
    auto b = evaluate(op_hand | table | t);
    if (a == b) draw += 1;
    else (a > b ? win : lose) += 1;
    deck ^= t;
  }

  int c;
  cin >> c;
  cout << c * (win * 2 + draw) / 2 / (win + draw + lose) << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while (T --> 0) solve();

  return 0;
}
