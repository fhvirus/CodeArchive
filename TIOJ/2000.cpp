#define _PRINT_PYTHON

#include "lib2000.h"

pos_type operator + (const pos_type &a, const pos_type &b)
{ return { a.x + b.x, a.y + b.y }; }
pos_type operator - (const pos_type &a, const pos_type &b)
{ return { a.x - b.x, a.y - b.y }; }
pos_type operator * (const pos_type &a, const float &b)
{ return { a.x * b, a.y * b }; }
pos_type operator / (const pos_type &a, const float &b)
{ return { a.x / b, a.y / b }; }
float dist2(const pos_type &a) { return a.x * a.x + a.y * a.y; }
float dist(const pos_type &a) { return sqrt(dist2(a)); }
pos_type normal(const pos_type &a) { return dist(a) < 1e-6 ? pos_type{0, 0} : a / dist(a); }

void init() { return; }

// a pushing b away
pos_type calc_force(const pos_type &a, const pos_type &b)
{ return normal(b - a) / dist2(a - b); }

pos_type play(){
  pos_type my_pos = get_pos();

  pos_type force = {0, 0};

  auto balls = get_ball();
  for (auto ball : balls)
    force = force + calc_force(ball, my_pos);

  balls = get_ball_spec();
  for (auto ball : balls)
    force = force + calc_force(ball, my_pos);

  auto tools = get_tool();
  for (auto tool : tools)
    force = force + calc_force(tool.pos, my_pos) * -3;

  // penalty for too close to wall
  pos_type wall_pen = {
    50 / pow(0.01 - my_pos.x, 2) + -50 / pow(100.01 - my_pos.x, 2),
    25 / pow(0.01 - my_pos.y, 2) + -25 / pow(50.01 - my_pos.y, 2)
  };
  force = force + wall_pen;

  return my_pos + force;
}

