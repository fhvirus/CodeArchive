#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <queue>

// Hu-Tucker algorithm
// Ref: https://repository.rit.edu/cgi/viewcontent.cgi?article=7489&context=theses

const int kN = 200002;
const int64_t INF = 1e18;
int n;
int64_t P[kN];

// Skew heap

struct Node {
  int64_t val;
  Node *l, *r;
  Node (int64_t v = INF) : val(v), l(nullptr), r(nullptr) {}
};
Node *merge(Node *u, Node *v) {
  if (!u or !v) return u ?: v;
  if (u->val >= v->val) std::swap(u, v);
  u->r = merge(u->r, v);
  std::swap(u->l, u->r);
  return u;
}
Node *pop(Node *u) { return merge(u->l, u->r); }
int64_t get_val(Node *u) { return u ? u->val : INF; }
int64_t get_val2(Node *u) { return std::min(get_val(u->l), get_val(u->r)); }

template <class T>
using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

min_heap<std::pair<int64_t, int>> mpq;
int link[kN][2];
int64_t cost[kN];
Node nds[kN], *hpq[kN];
Node *new_node(int64_t v) {
  static int t = 0;
  nds[t] = Node(v);
  return &nds[t++];
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%ld", P + i);
  P[0] = P[n+1] = INF;

  for (int i = 0; i <= n + 1; ++i) {
    link[i][0] = i - 1;
    link[i][1] = i + 1;
    hpq[i] = NULL;
    if (i < n) {
      cost[i] = P[i] + P[i + 1];
      mpq.emplace(cost[i], i);
    }
  }

  auto update = [&](int u) -> void {
    cost[u] = std::min({
      P[u] + P[link[u][1]],
      P[u] + get_val(hpq[u]),
      get_val(hpq[u]) + P[link[u][1]],
      get_val(hpq[u]) + get_val2(hpq[u])
    });
    mpq.emplace(cost[u], u);
  };

  int64_t ans = 0;
  for (int _ = 1; _ < n; ++_) {
    while (mpq.top().first != cost[mpq.top().second]) mpq.pop();
    auto [c, i] = mpq.top(); mpq.pop();
    ans += c;

    bool merge_l = false, merge_r = false;
    if (P[i] + P[link[i][1]] == c) {
      merge_l = merge_r = true;
    } else if (P[i] + get_val(hpq[i]) == c) {
      hpq[i] = pop(hpq[i]);
      merge_l = true;
    } else if (get_val(hpq[i]) + P[link[i][1]] == c) {
      hpq[i] = pop(hpq[i]);
      merge_r = true;
    } else hpq[i] = pop(pop(hpq[i]));

    Node *u = new_node(c);
    hpq[i] = merge(hpq[i], u);

    if (merge_r) {
      int nxt = link[i][1], nnxt = link[nxt][1];
      link[nnxt][0] = i, link[i][1] = nnxt;
      hpq[i] = merge(hpq[i], hpq[nxt]);
      update(i);
      cost[nxt] = INF;
    }
    if (merge_l) {
      int prv = link[i][0], nxt = link[i][1];
      link[prv][1] = nxt, link[nxt][0] = prv;
      hpq[prv] = merge(hpq[prv], hpq[i]);
      update(prv);
      cost[i] = INF;
    }
    if (!merge_l and !merge_r) update(i);
  }

  printf("%ld\n", ans);

  return 0;
}
