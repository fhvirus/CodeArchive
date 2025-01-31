
/*
   Odometer simulator
   Copyright © 2012 Giovanni Mascellani <mascellani@poisson.phc.unipi.it>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <assert.h>

// GRID SIDE
//#define SIDE 256

char grid[SIDE][SIDE];
int posx = 0, posy = 0;
int dir = 0;
int step_num = 0, ip = 0;
int max_steps;

int program[][2] = {
  // PROGRAM DATA
};

#define OP_LEFT 0
#define OP_RIGHT 1
#define OP_MOVE 2
#define OP_GET 3
#define OP_PUT 4
#define OP_HALT 5
#define OP_JUMP 6
#define OP_BORDERJ 7
#define OP_PEBBLEJ 8

int movex[4] = { 0, -1, 0, 1 };
int movey[4] = { -1, 0, 1, 0 };

volatile int signalled = 0;

void signal_handler(int signal_num) {

  signalled = 1;

}

int looking_border() {

  int newx = posx + movex[dir];
  int newy = posy + movey[dir];
  return !((0 <= newx) && (newx < SIDE) && (0 <= newy) && (newy < SIDE));

}

int main() {

  int i, j;

  /* Set up the signal handler */
  struct sigaction act;
  memset(&act, 0, sizeof(act));
  act.sa_handler = signal_handler;
  sigaction(SIGUSR1, &act, NULL);
  sigaction(SIGINT, &act, NULL);

  /* Read grid */
  int tmp;
  tmp = scanf("%d %d %d %d %d %d", &posx, &posy, &dir, &step_num, &ip, &max_steps);
  assert(tmp > 0);
  for (i = 0; i < SIDE; i++) {
    for (j = 0; j < SIDE; j++) {
      tmp = scanf("%hhd", &grid[i][j]);
      assert(tmp > 0);
    }
  }

  /* Execute program */
  int halting = 0;
  int killed = 0;
  while (1) {
    /* Detect termination: end of code */
    if (ip >= sizeof(program) / sizeof(program[0])) {
      halting = 1;
    }

    /* Detect termination: too many steps */
    if ((max_steps != -1) && (step_num >= max_steps) && (!halting)) {
      halting = 1;
      killed = 1;
    }

    /* Detect termination: signal */
    if (signalled) {
      halting = 1;
    }

    if (halting) break;

    /* Decode instruction data */
    int op_code = program[ip][0];
    int data = program[ip][1];
    int jumped = 0;

    /* Execute instruction */
    switch (op_code) {
    case OP_LEFT:
      dir = (dir + 1) % 4;
      break;
    case OP_RIGHT:
      dir = (dir + 3) % 4;
      break;
    case OP_MOVE:
      if (!looking_border()) {
	posx = posx + movex[dir];
	posy = posy + movey[dir];
      }
      break;
    case OP_GET:
      if (grid[posx][posy] > 0)
	grid[posx][posy] -= 1;
      break;
    case OP_PUT:
      if (grid[posx][posy] < 15)
	grid[posx][posy] += 1;
      break;
    case OP_HALT:
      halting = 1;
      jumped = 1;
      break;
    case OP_JUMP:
      ip = data;
      jumped = 1;
      break;
    case OP_BORDERJ:
      if (looking_border()) {
	ip = data;
	jumped = 1;
      }
      break;
    case OP_PEBBLEJ:
      if (grid[posx][posy] > 0) {
	ip = data;
	jumped = 1;
      }
      break;
    }

    /* Increment IP and step number */
    if (!jumped) ip++;
    step_num++;
  }

  /* Write final grid and execution data */
  printf("%d %d %d %d %d %d\n", posx, posy, dir, step_num, ip, killed);
  for (i = 0; i < SIDE; i++) {
    for (j = 0; j < SIDE; j++) {
      printf("%hhd ", grid[i][j]);
    }
    printf("\n");
  }

  return 0;

}
