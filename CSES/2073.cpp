#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Treap {
  struct Node {
    static uint32_t rnd() {
      static uint32_t x = 131;
      return ++(x *= 0xdefaced);
    }
    uint32_t pri;
    int val, siz;
    bool tag;
    Node *lc, *rc;
    Node() = default;
    Node(int v) : pri(rnd()), val(v), siz(1), tag(false), lc(0), rc(0) {}
  };
  vector<Node> nd;
  int tot;
  Treap(int n) : nd(n), tot(0) {}
  inline Node* newNode(int v) {
    if (tot == sz(nd)) nd.resize(tot * 2);
    return &(nd[tot++] = Node(v));
  }
  int siz(const Node* u) { return u ? u->siz : 0; }
  void update(Node* u) {
    if (!u) return;
    swap(u->lc, u->rc);
    u->tag ^= 1;
  }
  Node* push(Node* u) {
    if (!u) return 0;
    if (u->tag) {
      update(u->lc);
      update(u->rc);
      u->tag = false;
    }
    return u;
  }
  Node* pull(Node* u) {
    u->siz = siz(u->lc) + 1 + siz(u->rc);
    return u;
  }
  Node* merge(Node* u, Node* v) {
    if (!push(u) or !push(v)) return u ?: v;
    if (u->pri > v->pri) {
      u->rc = merge(u->rc, v);
      return pull(u);
    }
    v->lc = merge(u, v->lc);
    return pull(v);
  }
  pair<Node*, Node*> split(Node* u, int k) {
    if (!push(u)) return {0, 0};
    if (k <= siz(u->lc)) {
      auto [a, b] = split(u->lc, k);
      u->lc = b;
      return {a, pull(u)};
    }
    auto [a, b] = split(u->rc, k - siz(u->lc) - 1);
    u->rc = a;
    return {pull(u), b};
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  string s;
  cin >> s;

  Treap treap(n);
  Treap::Node* root = 0;
  rep (i, 0, n) root = treap.merge(root, treap.newNode(i));

  for (int l, r, i = 0; i < m; ++i) {
    cin >> l >> r;
    l -= 1;

    Treap::Node *a, *b, *c;
    tie(root, c) = treap.split(root, r);
    tie(a, b) = treap.split(root, l);
    treap.update(b);
    root = treap.merge(treap.merge(a, b), c);
  }

  vi ord;
  const auto flatten = [&](const auto& dfs, Treap::Node* u) -> void {
    treap.push(u);
    if (u->lc) dfs(dfs, u->lc);
    ord.push_back(u->val);
    if (u->rc) dfs(dfs, u->rc);
  };
  flatten(flatten, root);

  for (int i : ord) cout << s[i];
  cout << '\n';

  return 0;
}
