#include <bits/stdc++.h>
using namespace std;

struct Val {
  int cnt, l, r;
  Val(int c = -1) : cnt(1), l(c), r(c) {}
  Val(int _cnt, int _l, int _r) : cnt(_cnt), l(_l), r(_r) {}
  Val operator + (const Val& o) const
  { return Val(cnt + o.cnt - (r == o.l), l, o.r); }
};
struct Tag {
  bool f; int c;
  Tag(bool _f = false, int _c = -1) : f(_f), c(_c) {}
  Tag operator + (const Tag& o) const { return Tag(f xor o.f, o.c == -1 ? c : o.c); }
  Val operator() (Val v) const {
    if (c != -1) return Val(c);
    if (f) swap(v.l, v.r);
    return v;
  }
};

struct Node {
  static mt19937 mt;
  Node *l = 0, *r = 0;
  int c, s; Val val; Tag tag;
  uint64_t y;
  Node(int _c = -1) : c(_c), s(1), val(c), tag(), y(mt()) {}
  void upd(Tag t) {
    val = t(val);
    tag = tag + t;
    if (t.f) swap(l, r);
    if (t.c != -1) c = t.c;
  }
  void pull() {
    val = Val(c), s = 1;
    if (l != nullptr) val = l->val + val, s += l->s;
    if (r != nullptr) val = val + r->val, s += r->s;
  }
  void push() {
    if (l != nullptr) l->upd(tag);
    if (r != nullptr) r->upd(tag);
    tag = Tag();
  }
};
mt19937 Node::mt(7122);

pair<Node*, Node*> split(Node* n, int k) {
  if (n == nullptr) return {};
  n->push();
  int ls = (n->l == nullptr ? 0 : n->l->s);
  if (ls >= k) {
    auto [a, b] = split(n->l, k);
    n->l = b;
    n->pull();
    return {a, n};
  }
  auto [a, b] = split(n->r, k - ls - 1);
  n->r = a;
    n->pull();
  return {n, b};
}

Node* merge(Node* l, Node* r) {
  if (l == nullptr) return r;
  if (r == nullptr) return l;
  l->push(); r->push();
  if (l->y > r->y) {
    l->r = merge(l->r, r);
    return l->pull(), l;
  }
  r->l = merge(l, r->l);
  return r->pull(), r;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, C;
  cin >> N >> C;

  vector<Node> nds(N);
  Node* rt = nullptr;
  for (int c, i = 0; i < N; ++i) {
    cin >> c;
    nds[i] = Node(c);
    rt = merge(rt, &nds[i]);
  }

  int Q;
  cin >> Q;

  for (int i, j, k; Q --> 0; ) {
    string cmd;
    cin >> cmd;
    if (cmd[0] == 'C') {
      if (cmd[1] == 'U') {
        auto v = rt->val;
        cout << v.cnt - (v.cnt > 1 and v.l == v.r) << '\n';
      } else {
        cin >> i >> j; --i, --j;
        auto [a, b] = split(rt, i);
        if (j < i) {
          auto [c, d] = split(a, j + 1);
          cout << (b->val + c->val).cnt << '\n';
          rt = merge(merge(c, d), b);
        } else {
          auto [c, d] = split(b, j - i + 1);
          cout << (c->val).cnt << '\n';
          rt = merge(a, merge(c, d));
        }
      }
      continue;
    }
    if (cmd[0] == 'R') {
      cin >> k;
      auto [a, b] = split(rt, N - k);
      rt = merge(b, a);
    }
    if (cmd[0] == 'F') {
      auto [a, b] = split(rt, 1);
      b->upd(Tag(true));
      rt = merge(a, b);
    }
    if (cmd[0] == 'S') {
      cin >> i >> j; --i, --j;
      if (i == j) continue;
      if (i > j) swap(i, j);
      auto [b, a] = split(rt, j + 1);
      auto [c, nj] = split(b, j);
      auto [e, d] = split(c, i + 1);
      auto [f, ni] = split(e, i);
      rt = merge(merge(merge(f, nj), merge(d, ni)), a);
    }
    if (cmd[0] == 'P') {
      cin >> i >> j >> k; --i, --j;
      Tag t(false, k);
      if (j + 1 == i or (i == 0 and j == N - 1)) {
        rt->upd(t);
        continue;
      }
      auto [a, b] = split(rt, i);
      if (j < i) {
        auto [c, d] = split(a, j + 1);
        b->upd(t), c->upd(t);
        rt = merge(merge(c, d), b);
      } else {
        auto [c, d] = split(b, j - i + 1);
        c->upd(t);
        rt = merge(a, merge(c, d));
      }
    }
  }

  return 0;
}
