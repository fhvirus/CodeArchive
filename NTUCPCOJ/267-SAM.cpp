#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct SuffixAutomaton {
  enum { sigma = 26, first = 'a' };
  struct Node {
    int len, link, next[sigma]; ll cnt;
    Node(int v = 0) : len(0), link(0), cnt(0)
    { fill(next, next + sigma, v); }
  };
  vector<Node> nd;
  vi ord;
  SuffixAutomaton() : nd(1) { nd[0].link = -1; nd.reserve(6000006); }
  int insert(const string &s) {
    assert(!s.empty());
    int u = 0;
    for (char c : s) {
      int &v = nd[u].next[c - first];
      if (v == 0) { u = v = sz(nd); nd.emplace_back(); }
      else u = v;
      nd[u].cnt += 1;
    }
    return u;
  }
  int extend(int u, int c) {
    int v = nd[u].next[c];
    nd[v].len = nd[u].len + 1;
    int p = nd[u].link;
    while (p != -1 && nd[p].next[c] == 0)
      nd[p].next[c] = v, p = nd[p].link;
    if (p == -1) return nd[v].link = 0, v;
    int y = nd[p].next[c];
    if (nd[p].len + 1 == nd[y].len) return nd[v].link = y, v;
    int clone = sz(nd); nd.emplace_back();
    rep (i, 0, sigma) nd[clone].next[i] =
      (nd[nd[y].next[i]].len > 0 ? nd[y].next[i] : 0);
    nd[clone].len = nd[p].len + 1;
    while (p != -1 && nd[p].next[c] == y)
      nd[p].next[c] = clone, p = nd[p].link;
    nd[nd[v].link = clone].link = nd[y].link;
    nd[y].link = clone;
    return v;
  }
  void build() {
    queue<int> q;
    for (q.push(0); !q.empty(); q.pop()) {
      int u = q.front();
      rep (c, 0, sigma) if (nd[u].next[c] != 0)
        q.push(extend(u, c));
    }
    vi cnt(sz(nd)); ord.resize(sz(nd) - 1);
    rep (i, 1, sz(nd)) ++cnt[nd[i].len];
    partial_sum(all(cnt), begin(cnt));
    rep (i, 1, sz(nd)) ord[--cnt[nd[i].len]] = i;
    for (int i = sz(ord) - 1; i >= 0; --i)
      nd[nd[ord[i]].link].cnt += nd[ord[i]].cnt;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string S, T;
  cin >> S >> T;

  SuffixAutomaton sam;
  sam.insert(S);
  sam.build();

  int u = 0, l = 0, r = 0, q;
  cin >> q;
  for (int a, b; q --> 0; ) {
    cin >> a >> b; a -= 1;
    bool fail = false;
    if (r < a) u = 0, l = r = a;
    while (r < b) {
      while (u != 0 and l < a and sam.nd[u].next[T[r] - sam.first] == 0) {
        l = r - sam.nd[sam.nd[u].link].len;
        u = sam.nd[u].link;
      }
      int v = sam.nd[u].next[T[r] - sam.first];
      if (v == 0) {
        fail = true;
        break;
      }
      u = v, r += 1;
    }
    while (u != 0 and l < a and sam.nd[sam.nd[u].link].len >= b - a) {
      l = r - sam.nd[sam.nd[u].link].len;
      u = sam.nd[u].link;
    }
    cout << (fail ? 0 : sam.nd[u].cnt) << '\n';
  }

  return 0;
}
