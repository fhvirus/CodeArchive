#include <bits/stdc++.h>
using namespace std;

template<class... Ts>
struct Match : Ts... { using Ts::operator()...; };

enum struct Op : int8_t { NOT = 0, OR, NAND, AND, NOR, XOR, NXOR };
const string OPS[7] = {"not", "or", "nand", "and", "nor", "xor", "xnor"};
optional<Op> get_op(const string& s) {
  auto it = ranges::find(OPS, s);
  if (it == end(OPS)) return {};
  return (Op)(it - begin(OPS));
}
bool eval(Op o, bool a, bool b) {
  using enum Op;
  switch (o) {
    case OR : return a or b;
    case NAND : return not (a and b);
    case AND : return a and b;
    case NOR : return not (a or b);
    case XOR : return a xor b;
    case NXOR : return not (a xor b);
    default: return false;
  }
}

void clean_up(auto& cnf) {
  int s = 0;
  for (int i = 0; i < (int)size(cnf); ++i) {
    auto &c = cnf[i];
    ranges::sort(c);
    c.erase(ranges::unique(c).begin(), end(c));
    bool taut = false;
    for (int v : c) taut |= (ranges::find(c, ~v) != end(c));
    if (not taut) cnf[s++] = c;
  }
  cnf.resize(s);
}
auto process_formula(int tot, auto formula) {
  vector<variant<Op, int>> stk;
  vector<vector<int>> cnf;
  for (auto t : formula) {
    stk.push_back(t);
    int s = (int)size(stk);
    const auto m1 = Match {
      [&]([[maybe_unused]] Op o) { return false; },
      [&](int a) {
        if (s == 1) return false;
        const auto m2 = Match {
          [&](Op o) {
            if (o == Op::NOT) {
              for ([[maybe_unused]] int i : {0, 1})
                stk.pop_back();
              stk.emplace_back(~a);
              s -= 1;
              return true;
            }
            return false;
          },
          [&](int b) {
            Op o = get<Op>(stk[s - 3]);
            int c = tot++;
            for (bool va : {0, 1}) for (bool vb : {0, 1}) {
              bool res = eval(o, va, vb);
              cnf.push_back({va ? ~a : a, vb ? ~b : b, res ? c : ~c });
            }
            for ([[maybe_unused]] int i : {0, 1, 2})
              stk.pop_back();
            stk.emplace_back(c);
            s -= 2;
            return true;
          }
        };
        return visit(m2, stk[s - 2]);
      }
    };
    while (s > 0 and visit(m1, stk[s - 1]));
  }
  cnf.push_back({ ~get<int>(stk[0]) });
  clean_up(cnf);
  return pair(tot, cnf);
}

// mainly by Claude
struct SatCDCL {
  int n;
  vector<vector<int>> cls, watch;
  vector<int8_t> val, phase;
  vector<int> lvl, reason, seen, trail, branch_t;
  vector<double> act;
  int head = 0, seen_stamp = 0;
  double act_inc = 1.0;
  bool ok = true;

  SatCDCL(int n_) : n(n_), watch(2 * n_), val(n_, -1), phase(n_, -1),
    lvl(n_, 0), reason(n_, -1), seen(n_, 0), act(n_, .0) {}

  static int get_id(int v) { return v < 0 ? ~v : v; }
  static int lit_id(int v) { return v >= 0 ? 2 * v : 2 * get_id(v) + 1; }
  int get_val(int v) const {
    int id = get_id(v);
    return val[id] == -1 ? -1 : val[id] == (v >= 0);
  }

  bool enqueue(int v, int ci) {
    int cur = get_val(v);
    if (cur != -1) return cur == 1;
    int id = get_id(v);
    val[id] = (v >= 0);
    lvl[id] = (int)size(branch_t);
    reason[id] = ci;
    trail.push_back(v);
    return true;
  }

  int add_clause(vector<int> lits, bool unit_ok = true) {
    if (empty(lits)) { ok = false; return -1; }
    vector<int> c;
    for (int v : lits) {
      if (ranges::count(c, ~v)) return -1;
      if (ranges::count(c, v) == 0) c.push_back(v);
    }
    int ci = (int)size(cls);
    for (int v : c) act[get_id(v)] += 1.0;
    if (size(c) == 1) ok &= not (unit_ok and not enqueue(c[0], ci));
    else for (int i : {0, 1}) watch[lit_id(c[i])].push_back(ci);
    cls.push_back(std::move(c));
    return ci;
  }

  int propagate() {
    while (head < (int)size(trail)) {
      int v = ~trail[head++];
      auto &w = watch[lit_id(v)];
      int kept = 0;
      for (int p = 0; p < (int)size(w); ++p) {
        int ci = w[p]; auto &c = cls[ci];
        if (c[0] != v) swap(c[0], c[1]);
        if (get_val(c[1]) == 1) { w[kept++] = ci; continue; }

        int repl = -1;
        for (int i = 2; i < (int)size(c); ++i)
          if (get_val(c[i]) != 0) { repl = i; break; }
        if (repl != -1) {
          swap(c[0], c[repl]);
          watch[lit_id(c[0])].push_back(ci);
          continue;
        }

        w[kept++] = ci;
        if (not enqueue(c[1], ci)) {
          for (++p; p < (int)size(w); ++p) w[kept++] = w[p];
          w.resize(kept);
          return ci;
        }
      }
      w.resize(kept);
    }
    return -1;
  }

  auto analyze(int confl) {
    ++seen_stamp;
    vector<int> learned(1);
    int n_bad = 0, bad = INT_MIN, tp = (int)size(trail) - 1;
    while (true) {
      for (int v : cls[confl]) {
        int id = get_id(v);
        if (bad != INT_MIN and id == get_id(bad)) continue;
        if (seen[id] == seen_stamp or lvl[id] == 0) continue;
        seen[id] = seen_stamp;
        if ((act[id] += act_inc) > 1e100) {
          act_inc *= 1e-100;
          for (double &a : act) a *= 1e-100;
        }
        if (lvl[id] == (int)size(branch_t)) ++n_bad;
        else learned.push_back(v);
      }
      while (seen[get_id(trail[tp])] != seen_stamp) --tp;
      bad = trail[tp--];
      seen[get_id(bad)] = 0;
      if (--n_bad == 0) break;
      confl = reason[get_id(bad)];
    }
    learned[0] = ~bad;
    int back_lvl = 0, hp = 1;
    for (int i = 1; i < (int)size(learned); ++i) {
      int L = lvl[get_id(learned[i])];
      if (L > back_lvl) back_lvl = L, hp = i;
    }
    if (size(learned) > 1) swap(learned[1], learned[hp]);
    return pair(learned, back_lvl);
  }

  void backtrack(int to) {
    if ((int)size(branch_t) <= to) return;
    int sz = branch_t[to];
    for (int i = (int)size(trail) - 1; i >= sz; --i) {
      int id = get_id(trail[i]);
      phase[id] = val[id];
      val[id] = -1; lvl[id] = 0; reason[id] = -1;
    }
    trail.resize(sz);
    branch_t.resize(to);
    head = min(head, sz);
  }

  bool solve(auto& cnf) {
    for (auto &c : cnf) add_clause(c);
    if (not ok) return false;
    for (int t = 0, lim = 100, dlim = 100; ;) {
      if (int confl = propagate(); confl != -1) {
        if ((int)size(branch_t) == 0) return false;
        auto [learned, to] = analyze(confl);
        backtrack(to);
        int ci = add_clause(learned, false);
        if (not enqueue(learned[0], ci)) return false;
        ++t, act_inc *= 1.05;
        continue;
      }
      if (t >= lim and (int)size(branch_t) > 0) {
        backtrack(0);
        lim = t + (dlim = dlim * 3 / 2);
        continue;
      }
      int v = -1;
      for (int i = 0; i < n; ++i)
        if (val[i] == -1 and (v == -1 or act[i] > act[v])) v = i;
      if (v == -1) return true;
      branch_t.push_back((int)size(trail));
      enqueue(phase[v] == 1 ? v : ~v, -1);
    }
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  int tot = 0;
  vector<int> id(N, -1);
  vector<variant<Op, int>> formula;
  for (string s; cin >> s; ) {
    if (auto op = get_op(s); op) {
      formula.emplace_back(*op);
      continue;
    }
    int x = stoi(s.substr(1));
    if (id[x] == -1) id[x] = tot++;
    formula.emplace_back(id[x]);
  }

  auto [n, cnf] = process_formula(tot, formula);
  SatCDCL solver(n);
  if (not solver.solve(cnf)) exit(-1);

  for (int i = 0; i < N; ++i)
    cout << (id[i] != -1 and solver.val[id[i]] == 1) << '\n';

  return 0;
}
