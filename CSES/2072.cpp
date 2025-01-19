#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

uint32_t rnd() {
  static uint32_t x = 712271227;
  return ++(x *= 0xdefaced);
}

struct Node {
  Node *l, *r;
  uint32_t siz, pri;
  char val;
  Node (char v) : l(0), r(0), siz(1), pri(rnd()), val(v) {}
  void pull();
};
uint32_t cnt(Node *u) { return u ? u->siz : 0; }
void Node::pull() { siz = 1 + cnt(l) + cnt(r); }

pair<Node*, Node*> split(Node *u, uint32_t k) {
  if (!u) return {};
  if (cnt(u->l) >= k) {
    auto [a, b] = split(u->l, k);
    u->l = b;
    u->pull();
    return {a, u};
  }
  auto [a, b] = split(u->r, k - cnt(u->l) - 1);
  u->r = a;
  u->pull();
  return {u, b};
}

Node* merge(Node *u, Node *v) {
  if (!u || !v) return u ?: v;
  if (u->pri > v->pri) {
    u->r = merge(u->r, v);
    u->pull();
    return u;
  }
  v->l = merge(u, v->l);
  v->pull();
  return v;
}

Node* ins(Node* t, Node* u, int pos) {
  auto [a, b] = split(t, pos);
  return merge(a, merge(u, b));
}

void move(Node *&u, int l, int r, int k) {
  Node *a, *b, *c;
  tie(a, b) = split(u, l); tie(b, c) = split(b, r - l);
  if (k <= l) u = merge(ins(a, b, k), c);
  else u = merge(a, ins(c, b, k - r));
}

void print(Node *u) {
  if (!u) return;
  print(u->l);
  cout << u->val;
  print(u->r);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  string s;
  cin >> s;

  vector<Node> nds;
  for (char c : s) nds.emplace_back(c);
  Node* root = 0;
  rep (i, 0, n) root = merge(root, &nds[i]);

  for (int l, r, i = 0; i < m; ++i) {
    cin >> l >> r; l -= 1;
    move(root, l, r, n);
  }

  print(root);
  cout << '\n';

  return 0;
}
