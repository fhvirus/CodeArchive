#include "lib2014.h"

#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;

typedef long long unsigned int ull;
typedef __int128 i128;
typedef unsigned __int128 u128;
typedef pair<int, int> pii;

void mul_u128(u128 u, u128 v, u128& rh, u128& rl) {
  auto H = [](const u128& a) { return (a >> 64); };
  auto L = [](const u128& a) { return (a << 64) >> 64; };
  rh = H(u) * H(v), rl = L(u) * L(v);
  for (auto t : { H(u) * L(v), L(u) * H(v) }) {
    ull buf;
    if (__builtin_uaddll_overflow(ull(L(t)), ull(H(rl)), &buf)) ++rh;
    rl = (u128(buf) << 64) | L(rl);
    rh += H(t);
  }
}

struct Hu_Shing {
  struct Arc;
  struct ArcP_Cmp { bool operator () (const Arc* l, const Arc* r) const { return *l < *r; } };
  struct Arc {
    int a, b, l_next, r_prev;
    Arc* par;
    __gnu_pbds::priority_queue<Arc*, ArcP_Cmp, __gnu_pbds::pairing_heap_tag> pq;
    i128 cost, fan_weight; // supporting weight = c / w
    Arc (int _a, int _b) : a(_a), b(_b), l_next(_a + 1), r_prev(_b - 1), par(this) {}
    bool operator < (const Arc& o) const {
      u128 h = cost, l = o.fan_weight, oh = o.cost, ol = fan_weight;
      mul_u128(h, l, h, l);
      mul_u128(oh, ol, oh, ol);
      return h == oh ? l < ol : h < oh;
    }
    Arc* get_hm() const { return empty(pq) ? nullptr : pq.top(); }
    void eat() {
      Arc* hm = pq.top(); pq.pop();
      fan_weight += hm->fan_weight;
      if (a == hm->a) l_next = hm->l_next;
      if (b == hm->b) r_prev = hm->r_prev;
      pq.join(hm->pq);
    }
  };

  int n;
  vector<i128> w, prod;
  i128 get_fan_weight(int a, int b) { return (prod[b] - prod[a]) - w[a] * w[b]; };

  void retrieve_all_arcs(vector<pii>& h_arcs) {
    vector<pii> stk, all; all.reserve(n - 1);
    pii last(-1, -1);
    for (int i = n, j = 0; i >= 0; --i) {
      while (not empty(stk) and stk.back().first >= i) {
        all.push_back(stk.back());
        last = stk.back();
        stk.pop_back();
      }
      if (not empty(stk)) {
        auto [l, r] = stk.back();
        // must connect to n before 0, otherwise erase(2) at end would erase wrong arc
        (w[l] < w[r] ? r : l) = i;
        if (l + 1 != r and pii(l, r) != last and
            not (j < int(size(h_arcs)) and pii(l, r) == h_arcs[j]))
          all.emplace_back(l, r);
      }
      while (j < int(size(h_arcs)) and h_arcs[j].second >= i)
        stk.push_back(h_arcs[j++]);
    }
    // must be one degenerated/redundant and (0, n)
    all.erase(end(all) - 2, end(all));
    h_arcs.swap(all);
  }

  void find_ceiling_and_eat_children(Arc &h) {
    if (h.a + 2 == h.b) { // base case
      h.cost = i128(w[h.a]) * w[h.a + 1] * w[h.b];
      return;
    }
    i128 wh = min(w[h.a], w[h.b]);
    // Step 1: delete arcs impossible to be in l-opt in subtree
    for (Arc* hm; (hm = h.get_hm()) and hm->cost >= hm->fan_weight * wh; )
      h.eat(), hm->par = nullptr;
    // calculate cost
    int side = (w[h.a] <= w[h.b] ? h.l_next : h.r_prev);
    h.cost = wh * (h.fan_weight - wh * w[side] + w[h.a] * w[h.b]);
    // Step 2: Merge children and find ceiling
    for (Arc* hm; (hm = h.get_hm()) and not (*hm < h); )
      h.eat(), h.cost += hm->cost, hm->par = &h;
  }

  vector<pii> ans_arcs;
  Hu_Shing (int _n, i128 _w[]) : n(_n), prod(n + 2) {
    w.reserve(n + 1);
    copy(_w, _w + n, back_inserter(w));
    int shift = int(min_element(_w, _w + n) - _w);
    ranges::rotate(w, begin(w) + shift);
    w.push_back(w[0]);
    for (int i = 1; i <= n; ++i)
      prod[i] = prod[i - 1] + w[i - 1] * w[i];

    vector<Arc> arcs; arcs.reserve(n - 1);
    vector<int> stk_v;
    vector<Arc*> stk_a;
    const auto process_arcs = [&]() {
      Arc& h = arcs.back();
      h.fan_weight = get_fan_weight(h.a, h.b);
      while (not empty(stk_a) and h.a <= stk_a.back()->a) {
        Arc* hm = stk_a.back();
        if (h.a == hm->a) h.l_next = hm->b;
        if (h.b == hm->b) h.r_prev = hm->a;
        h.fan_weight -= get_fan_weight(hm->a, hm->b);
        h.pq.push(hm);
        stk_a.pop_back();
      }
      find_ceiling_and_eat_children(h);
      stk_a.emplace_back(&h);
    };
    for (int i = 0; i <= n; ++i) {
      while (size(stk_v) >= 2 and w[stk_v.back()] >= w[i]) {
        stk_v.pop_back();
        arcs.emplace_back(stk_v.back(), i);
        process_arcs();
      }
      stk_v.push_back(i);
    }

    for (Arc& h : arcs | views::reverse)
      if (h.par == nullptr or h.par->par == nullptr) h.par = nullptr;
      else ans_arcs.emplace_back(h.a, h.b);

    retrieve_all_arcs(ans_arcs);
    for (auto &[l, r] : ans_arcs) {
      l = (l + shift) % n, r = (r + shift) % n;
      if (l > r) swap(l, r);
    }
  }
};

void Solve(int N, __int128 h[], int ans[]) {
  if (N <= 3) { for (int i = 0; i < 2 * N - 3; ++i) ans[i] = i - 1; return;} // report!

  Hu_Shing sol(N, h);
  auto& arcs = sol.ans_arcs;
  ranges::sort(arcs, [](auto a, auto b) { return a.first == b.first ? a.second > b.second : a.first < b.first; });
  int t = 0;
  ans[t++] = -1;
  for (int i = 0, j = 0; i < N - 1; ++i) {
    while (j < int(size(arcs)) and arcs[j].first == i)
      ans[t++] = -1, ++j;
    ans[t++] = i;
  }
}
