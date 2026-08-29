#include <bits/stdc++.h>
using namespace std;

struct Val {
  int cnt; int16_t l, r;
  Val(int c = -1) : cnt(1), l(c), r(c) {}
  Val(int _cnt, int _l, int _r) : cnt(_cnt), l(_l), r(_r) {}
  Val operator + (const Val& o) const {
    if (l == -1 and r == -1) return o;
    if (o.l == -1 and o.r == -1) return *this;
    return Val(cnt + o.cnt - (r == o.l), l, o.r);
  }
};
struct Tag {
  int16_t c;
  Tag(int _c = -1) : c(_c) {}
  Tag operator + (const Tag& o) const { return Tag(o.c == -1 ? c : o.c); }
  Val operator() (Val v) const { return c == -1 ? v : Val(c); }
};

template <class V, class T> struct Seguki {
  int n; vector<V> val; vector<T> tag;
  Seguki(const vector<V>& v): n((int)size(v)), val(n*2), tag(n*2) {
    for (int i = 0; i < (int)size(v); ++i) val[i+n] = v[i];
    for (int i = n; --i; ) val[i] = val[i*2] + val[i*2+1];
  }
  void upd(int u, T t)
  { val[u] = t(val[u]); if (u < n) tag[u] = tag[u] + t; }
  void pull(int u)
  { while (u /= 2) val[u] = tag[u](val[u*2] + val[u*2+1]); }
  void push(int u) {
    for (int h = __lg(n)+1, i; --h;) {
      i = u >> h;
      upd(i * 2, tag[i]);
      upd(i * 2 + 1, tag[i]);
      tag[i] = T();
    }
  }
  void set(int p, V v) { push(p += n); val[p] = v; pull(p); }
  V get(int p) { push(p += n); return val[p]; }
  V query(int l, int r) {
    V rl, rr;
    for (push(l+=n), push((r+=n)-1); l < r; l /= 2, r /= 2) {
      if (l & 1) rl = rl + val[l++];
      if (r & 1) rr = val[--r] + rr;
    }
    return rl + rr;
  }
  void modify(int l, int r, T t) {
    int tl = (l += n), tr = (r += n) - 1;
    for (push(tl), push(tr); l < r; l >>= 1, r >>= 1) {
      if (l & 1) upd(l++, t);
      if (r & 1) upd(--r, t);
    }
    pull(tl); pull(tr);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, C;
  cin >> N >> C;

  vector<Val> vs(N);
  for (auto &v : vs) {
    int c; cin >> c;
    v = Val(c);
  }
  Seguki<Val, Tag> sgk(vs);

  int zero = 0, dir = 1;
  const auto T = [&](int p) {
    p = (p - zero) * dir;
    return p + N * ((p < 0) - (p >= N));
  };

  int Q;
  cin >> Q;

  for (int i, j, k; Q --> 0; ) {
    string cmd;
    cin >> cmd;

    if (cmd[0] == 'R') {
      cin >> k;
      zero = (zero + k < N ? zero + k : zero + k - N);
      continue;
    }
    if (cmd[0] == 'F') {
      dir = -dir;
      zero = (zero == 0 ? 0 : N - zero);
      continue;
    }
    if (cmd[0] == 'C' and cmd[1] == 'U') {
      auto v = sgk.query(0, N);
      cout << v.cnt - (v.cnt > 1 and v.l == v.r) << '\n';
      continue;
    }

    cin >> i >> j;
    i = T(i - 1), j = T(j - 1);
    if (dir == -1) swap(i, j);

    if (cmd[0] == 'S') {
      auto vi = sgk.get(i), vj = sgk.get(j);
      sgk.set(i, vj); sgk.set(j, vi);
    }
    if (cmd[0] == 'P') {
      cin >> k;
      Tag t(k);
      if (j < i) sgk.modify(i, N, t), sgk.modify(0, j + 1, t);
      else sgk.modify(i, j + 1, t);
    }
    if (cmd[0] == 'C' and cmd[1] == 'S') {
      auto v = (j < i) ? (sgk.query(i, N) + sgk.query(0, j + 1)) : sgk.query(i, j + 1);
      cout << v.cnt << '\n';
    }
  }

  return 0;
}
