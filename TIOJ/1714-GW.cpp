#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <utility>

const int kN = 200002;
const int64_t INF = 1e18;

// Begin Treap

uint32_t rnd() {
  static uint32_t x = 998244353;
  return ++(x *= 0xdefaced);
}

struct Node {
  int64_t val;
  uint32_t pri, siz;
  Node *l, *r;
  void pull();
} nds[kN + kN];

Node *new_node(int64_t val) {
  static int t = 0;
  nds[t] = {val, rnd(), 1, nullptr, nullptr};
  return &nds[t++];
}

uint32_t get_siz(Node *u) { return u ? u->siz : 0; }
void Node::pull() { siz = get_siz(l) + 1 + get_siz(r); }

Node *merge(Node *u, Node *v) {
  if (!u or !v) return !u ? v : u;
  if (u->pri > v->pri) {
    u->r = merge(u->r, v);
    u->pull();
    return u;
  }
  v->l = merge(u, v->l);
  v->pull();
  return v;
}

std::pair<Node*, Node*> split_by_siz(Node *o, uint32_t k) {
  if (!o) return {nullptr, nullptr};
  if (get_siz(o->l) >= k) {
    auto [u, v] = split_by_siz(o->l, k);
    o->l = v;
    o->pull();
    return {u, o};
  }
  auto [u, v] = split_by_siz(o->r, k - get_siz(o->l) - 1);
  o->r = u;
  o->pull();
  return {o, v};
}

int64_t min_val(Node *u) {
  if (!u) return INF + INF;
  while (u->l) u = u->l;
  return u->val;
}

int rank_of(Node *u, int64_t k) {
  int res = 0;
  while (u) {
    if (u->val < k) {
      res += get_siz(u->l) + 1;
      u = u->r;
    } else u = u->l;
  }
  return res;
}

// End Treap

int n;
int64_t P[kN];
int64_t ans = 0;

// combine R.M. pair recursively
// Using two treaps to maintain 2-decreasing chains in Garsia-Wachs algorithm.
Node *r[2];
void combine(int64_t val) {
  Node *u, *v;

  while (true) {
    int par = (get_siz(r[0]) + get_siz(r[1])) & 1;
    if (min_val(r[par]) > val) break;

    std::tie(u, r[0]) = split_by_siz(r[0], 1);
    std::tie(v, r[1]) = split_by_siz(r[1], 1);

    // new node of combined R.M. pair
    int64_t new_val = u->val + v->val;
    ans += new_val;

    // Beware of parity!
    par = (get_siz(r[0]) + get_siz(r[1])) & 1;
    int pos0 = rank_of(r[0], new_val) * 2 - (par) + 1;
    int pos1 = rank_of(r[1], new_val) * 2 - (1 - par) + 1;
    int pos = std::min(pos0, pos1);
    std::tie(u, r[0]) = split_by_siz(r[0], (pos + par) / 2);
    std::tie(v, r[1]) = split_by_siz(r[1], (pos + (1 - par)) / 2);
    if (pos == pos0) std::swap(u, v);

    combine(new_val);
    par = (get_siz(r[0]) + get_siz(r[1])) & 1;
    r[par] = merge(u, r[par]);
    r[1 - par] = merge(v, r[1 - par]);
  }

  uint32_t par = (get_siz(r[0]) + get_siz(r[1])) & 1;
  r[par] = merge(new_node(val), r[par]);
}

int main() {

  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%ld", P + i);
  P[0] = INF + 1, P[n + 1] = INF;

  r[0] = new_node(P[0]);
  r[1] = new_node(P[1]);
  for (int i = 2; i <= n + 1; ++i)
    combine(P[i]);

  printf("%ld\n", ans);

  return 0;
}
