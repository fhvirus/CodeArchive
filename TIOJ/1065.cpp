#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int) (x).size()

const double eps = 1e-8;
template <class T> int sgn(T x) { return (x > eps) - (x < -eps); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); }
	P perp() const { return P(-y, x); }
	P normal() const { return perp().unit(); }
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};
typedef Point<double> P;

// Don't care about endpoints
template<class P> bool onSegment(P s, P e, P p)
{ return sgn(p.cross(s, e)) == 0 && sgn((s-p).dot(e-p)) < 0; }

const double SQRT2 = sqrt(2);
const double INF = 1e18;

struct Segment {
  double y, l, r;
  Segment() {}
  Segment(double _y, double _l, double _r) :
    y(_y), l(_l), r(_r) {}
  bool is_on(P p) const { return onSegment(P(l, y), P(r, y), p); }
  double touch_time(P p, P v) const { // assuming that the player is falling
    // f: x = p.x + v.x * t
    //    y = p.y + v.y * t - t * t
    double d = v.y * v.y + 4 * (p.y - y);
    if (sgn(d) < 0) return INF;
    double ans = (-v.y - sqrt(d)) / -2;
    if (sgn(ans) < 0) return INF;
    double nx = p.x + v.x * ans;
    if (sgn(nx - l) <= 0 or sgn(r - nx) <= 0) return INF;
    return ans;
  }
  friend ostream& operator << (ostream& o, Segment s)
  { return o << "(" << s.l << ", " << s.y << ")--(" << s.r << ", " << s.y << ")"; }
};

struct Monster {
  char type;
  P o, r;
  double c;
  Monster(double sx, double sy, double tx, double ty, double c) :
    type('h'), o((sx + tx) / 2, (sy + ty) / 2), r((tx - sx) / 2, (ty - sy) / 2), c(c) {}
  Monster(double ox, double oy, double r, double c) :
    type('c'), o(ox, oy), r(r, 0), c(c) {}
  P get_pos(double t) const {
    if (type == 'h')
      return o + r * -cos(2 * M_PI * t / c);
    return o + r.rotate(2 * M_PI * t / c);
  }
};

struct Trajectory {
  double t0;
  P p0, v;
  bool fall;
  Trajectory(double _t0, P _p0, P _v, bool _fall) :
    t0(_t0), p0(_p0), v(_v), fall(_fall) {}
  P get_pos(double t) const {
    assert(sgn(t - t0) >= 0);
    const double dt = t - t0;
    return p0 + v * dt + P(0, fall ? -(dt * dt) : 0);
  }
};

struct Move {
  double t;
  string type;
  Move(double _t, string _type) : t(_t), type(_type) {}
  bool operator < (const Move& o) const
  { return sgn(t - o.t) < 0; }
  friend ostream& operator << (ostream& o, Move m)
  { return o << "(" << m.t << ", " << m.type << ")"; }
};

vector<Move> get_plan() {
  vector<Move> plan;
  string input;
  getline(cin, input);
  stringstream ss(input);
  string type;
  double dur, cur = 0;
  while (ss >> type >> dur) {
    plan.emplace_back(cur, type);
    cur += dur;
  }
  plan.emplace_back(cur, "none");
  return plan;
}

vector<Trajectory> simulate(P st_pos, const vector<Move>& plan, const vector<Segment>& segs) {
  auto get_on_seg = [&](P p) -> int {
    int res = -1;
    for (int i = 0; i < sz(segs); ++i)
      if (segs[i].is_on(p)) res = i;
    return res;
  };

  int move_ptr = 0;
  auto get_cur_move = [&](double t) -> Move {
    while (move_ptr + 1 < sz(plan) and sgn(t - plan[move_ptr + 1].t) >= 0) ++move_ptr;
    return plan[move_ptr];
  };
  auto get_move_end = [&]() -> double {
    if (move_ptr + 1 >= sz(plan)) return INF;
    return plan[move_ptr + 1].t;
  };

  vector<Trajectory> res;

  double t = 0;
  P p = st_pos, v(0, 0);
  int cur_seg = get_on_seg(st_pos);
  
  while (move_ptr + 1 < sz(plan) or cur_seg == -1) {
    cur_seg = get_on_seg(p);
    Move cur_move = get_cur_move(t);
    double end_t = get_move_end();
    bool fall = false;

    if (cur_seg == -1) { // moves are useless
      fall = true;
      for (auto seg : segs)
        end_t = min(end_t, t + seg.touch_time(p, v));
    } else {
      if (cur_move.type[1] == 'w') {
        if (cur_move.type[0] == 'r') {
          v = P(1, 0);
          end_t = min(end_t, t + (segs[cur_seg].r - p.x));
        } else {
          v = P(-1, 0);
          end_t = min(end_t, t + (p.x - segs[cur_seg].l));
        }
      } else if (cur_move.type[1] == 'j') {
        fall = true;
        if (cur_move.type[0] == 'u')
          v = P(0, 2);
        else v = P(cur_move.type[0] == 'r' ? SQRT2 : -SQRT2, SQRT2);

        for (auto seg : segs)
          end_t = min(end_t, t + seg.touch_time(p, v));
      } else v = P(0, 0);
    }

    res.emplace_back(t, p, v, fall);
    p = res.back().get_pos(end_t);
    if (fall) v = v + P(0, -2 * (end_t - t));
    t = end_t;
  }

  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int L;
  cin >> L;

  vector<Segment> segs(L);
  for (auto &[y, l, r]: segs)
    cin >> y >> l >> r;

  int N;
  cin >> N;

  vector<Monster> mons;
  for (int i = 0; i < N; ++i) {
    char type;
    cin >> type;
    if (type == 'h') {
      double sx, sy, ex, ey, c;
      cin >> sx >> sy >> ex >> ey >> c;
      mons.emplace_back(sx, sy, ex, ey, c);
    } else {
      assert(type == 'c');
      double ox, oy, r, c;
      cin >> ox >> oy >> r >> c;
      mons.emplace_back(ox, oy, r, c);
    }
  }

  P st_pos;
  cin >> st_pos.x >> st_pos.y;

  int M;
  cin >> M;
  cin.ignore();

  while (M --> 0) {
    vector<Move> plan = get_plan();
    vector<Trajectory> traj = simulate(st_pos, plan, segs);

    double end_t = traj.back().t0 + 1;
    bool ans = true;
    for (int i = 0, j = 0; sgn(i * 0.1 - end_t) <= 0 and ans; ++i) {
      const double t = i * 0.1;
      while (j + 1 < sz(traj) and sgn(traj[j + 1].t0 - t) <= 0) ++j;
      P pos = traj[j].get_pos(t);
      for (const auto& mon : mons)
        ans &= sgn((pos - mon.get_pos(t)).dist() - 0.5) >= 0;
    }
    cout << (ans ? "Y\n" : "N\n");
  }
  
  return 0;
}
