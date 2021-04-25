#pragma GCC optimize("Ofast")
#include<cstdio>
#define ull unsigned long long
inline ull PRNG(ull a, ull b) {
  static const ull table[3] = {0x9e3779b185ebca87, 0xc2b2ae3d27d4eb4f, 0x165667b19e3779f9};
  auto Mix = [](ull a, ull b) {
    a += b * table[1];
    a = (a << 31) | (a >> 33);
    return a * table[0];
  };
  ull v1 = Mix(-table[0], a);
  ull v2 = Mix(table[1], b);
  ull ret = ((v1 << 18) | (v1 >> 46)) + ((v2 << 7) | (v2 >> 57));
  ret ^= ret >> 33;
  ret *= table[1];
  ret ^= ret >> 29;
  ret *= table[2];
  ret ^= ret >> 32;
  return ret;
}
inline ull gcd(ull u, ull v){
    int shift;
    if (u == 0) return v;
    if (v == 0) return u;
    shift = __builtin_ctzll(u | v);
    u >>= __builtin_ctzll(u);
    do {
        v >>= __builtin_ctzll(v);
        // if (u > v) {
        //     // ull t = v;
        //     // v = u;
        //     // u = t;
        //     u ^= v;
        //     v ^= u; 
        //     u ^= v;
        // }  
        (u > v) && (u ^= v, v ^= u, u ^= v);
        v = v - u;
    } while (v != 0);
    return u << shift;
}
int main(){
    ull a, b, c = 0, aa, bb; int n;
    scanf("%d%llu%llu", &n, &a, &b);
    for(int i = 1; i <= n; ++i){
        bb = gcd(a, b);
        a = PRNG(b, bb);
        c = PRNG(c, bb);
        b = PRNG(a, bb);
    }
    printf("%llu", c);
}