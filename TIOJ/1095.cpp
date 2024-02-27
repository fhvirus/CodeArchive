#include <cstdio>
#include <cstring>
#include <algorithm>
#include <numeric>

#define rep(i, a, b) for (int i = a; i < (b); ++i)

template <class T, int kN = 30>
struct Matrix {
  int n, m;
  T a[kN][kN];
  Matrix (int _n = 0, int _m = 0) : n(_n), m(_m) {
    rep (i, 0, n) rep (j, 0, m) a[i][j] = 0;
  }
  Matrix operator + (const Matrix &o) const {
    Matrix r(n, m);
    rep (i, 0, n) rep (j, 0, m)
      r.a[i][j] = a[i][j] + o.a[i][j];
    return r;
  }
  Matrix operator - (const Matrix &o) const {
    Matrix r(n, m);
    rep (i, 0, n) rep (j, 0, m)
      r.a[i][j] = a[i][j] - o.a[i][j];
    return r;
  }
  Matrix operator * (const Matrix &o) const {
    Matrix r(n, o.m);
    rep (i, 0, n) rep (j, 0, o.m) rep (k, 0, m)
      r.a[i][j] += a[i][k] * o.a[k][j];
    return r;
  }
  Matrix dinv() const {
    T b[kN][kN * 2];
    rep (i, 0, n) rep (j, 0, n)
      b[i][j] = a[i][j], b[i][j + n] = (i == j);
    T det_mul = 1, det_div = 1;
    rep (r, 0, n) {
      rep (nr, r, n) {
        if (b[nr][r] == 0) continue;
        if (nr != r) {
          det_mul *= -1;
          rep (i, 0, 2 * n) std::swap(b[r][i], b[nr][i]);
        }
        break;
      }
      if (b[r][r] < 0) {
        det_div *= -1;
        rep (i, 0, 2 * n) b[r][i] *= -1;
      }

      rep (nr, r + 1, n) {
        while (b[nr][r] != 0) { // from kactl determinant
          T t = b[r][r] / b[nr][r];
          if (t) rep (i, r, 2 * n)
            b[r][i] -= b[nr][i] * t;
          rep (i, 0, 2 * n)
            std::swap(b[r][i], b[nr][i]);
          det_mul *= -1;
        }
      }
    }

    for (int r = n - 1; r >= 0; --r) {
      if (det_div % b[r][r] == 0) det_div /= b[r][r];
      else det_mul *= b[r][r];
      for (int nr = r - 1; nr >= 0; --nr) {
        if (b[nr][r] == 0) continue;
        T l = std::lcm(b[r][r], b[nr][r]);
        T ma = l / b[r][r], mb = l / b[nr][r];
        if (det_mul % mb == 0) det_mul /= mb;
        else det_div *= mb;
        rep (i, 0, 2 * n)
          b[nr][i] = b[nr][i] * mb - b[r][i] * ma;
      }
    }

    Matrix r(n, m);
    rep (i, 0, n) rep (j, 0, n)
      r.a[i][j] = b[i][n + j] * (det_mul / b[i][i] / det_div);
    return r;
  }
  void print() const {
    printf("[ ");
    rep (i, 0, n) rep (j, 0, m) {
      printf("%lld ", a[i][j]);
      if (j + 1 == m and i + 1 < n) printf("; ");
    }
    printf("]\n");
  }
  void read(char *buf) {
    n = 0, m = 0;
    for (int len;;) {
      if (sscanf(buf, "%lld%n", &a[n][m], &len) != 1) {
        char c;
        sscanf(buf, " %c", &c);
        if (c == ';') n += 1, m = 0, buf += 2;
        else break;
      } else m += 1, buf += len;
    }
    n += 1;
  }
};

Matrix<long long> var[26];

const int kB = 20002;
char buf[kB];

int main() {

  while (fgets(buf, kB, stdin) != NULL) {
    if (buf[0] == '\n') {
      rep (i, 0, 26) {
        var[i].print();
        var[i] = Matrix<long long>();
      }
      puts("");
      continue;
    }

    int id = buf[0] - 'a';
    if (buf[4] == '[') var[id].read(buf + 6);
    else {
      int a = buf[4] - 'a';
      if (strlen(buf) < 7) {
        var[id] = var[a];
        continue;
      }
      char op = buf[6];
      int b = buf[8] - 'a';
      if (op == '+') var[id] = var[a] + var[b];
      else if (op == '-') var[id] = var[a] - var[b];
      else if (op == '*') var[id] = var[a] * var[b];
      else if (op == '/') var[id] = var[a] * var[b].dinv();
      else var[id] = var[a].dinv() * var[b];
    }
  }
  rep (i, 0, 26) var[i].print();

  return 0;
}
