// Knapsack DP is harder than FFT.
#ifdef OWO
#include<bits/stdc++.h>
using namespace std;
#define debug(args...) SDF(#args, args)
template<class...T>void SDF(const char* s,T...a){int c=sizeof...(T);if(!c){cerr<<"\033[1;32mvoid\033[0m\n";return;}(cerr<<"\033[1;32m("<<s<<") = (",...,(cerr<<a<<(--c?", ":")\033[0m\n")));}
#else
#define debug(...) ((void)0)
#endif

#pragma GCC optimize("Ofast","unroll-loops","fast-math")
#include<unistd.h>
#include<cstdint>
#include<algorithm>
using namespace std;

typedef uint32_t uint;
typedef int64_t ll;
typedef uint64_t ull;
typedef __uint128_t u128;

// kN * kC^2 < MOD;
const uint kN = 1048576;
const uint kC = 1000000;
const uint kI = 6000006;
const ull MOD = 9097271247288401921;
const ull INV = 9351220758157713293;
const ull   G = 6;

constexpr ull mul(ull a, ull b) {
  u128 v = (u128)a * b;
  ull x = v >> 62;
  ull q = ((u128)x * INV) >> 64;

  ull ans = (ull)v - q * MOD;
	ans -= MOD; ans += MOD & ((ll) ans >> 63);
  return ans;
} 
//inline ull mul(ull a, ull b){
//	u128 c = (u128) a * b;
//	ull  q = c / MOD;
//	return c - (u128) q * MOD;
//}
inline ull mow(ull x, ull e){
	ull r = 1;
	for(; e; e >>= 1){
		if(e & 1) r = mul(r, x);
		x = mul(x, x);
	}
	return r;
}

uint N, M;
ull A[kN], B[kN], C[kN];
char buf[kI], *la, *ra, *lb, *rb;

ull W[kN];
int rev[kN];
void build(int n){
	W[0] = 1; ull w = mow(G, (MOD - 1) / n);
	for(int i = 1; i < n; ++i) W[i] = mul(W[i-1], w);

	rev[0] = 0;
	for(int i = 1, h = -1, l = 31 - __builtin_clz(n); i < n; ++i){
		if(!(i & (i - 1))) ++h;
		rev[i] = rev[i ^ (1<<h)] | (1<<(l-h-1));
	}
}
void NTT(int n, ull a[]){
	for(int i = 0; i < n; ++i)
		if(i < rev[i]) swap(a[i], a[rev[i]]);

	for(int len = 1; len < n; len <<= 1){
		for(int g = 0; g < n; g += len<<1){
			for(int i = 0; i < len; ++i){
				ull x = a[g + i];
				ull y = mul(a[g + i + len], W[n/len/2*i]);
				a[g + i] = x + y - MOD; a[g + i] += (MOD & (ll)a[g + i] >> 63);
				a[g + i + len] = x - y; a[g + i + len] += (MOD & (ll)a[g + i + len] >> 63);
			}
		}
	}
}

void calc(uint &n, char *l, char *r, ull a[kN]){
	reverse(l, r);
	n = 0;
	int cur = 0, bas = 1;
	for(char *i = l; i < r; ++i){
		cur += (*i - '0') * bas;
		bas *= 10;
		if(bas == kC){
			a[n++] = cur;
			cur = 0;
			bas = 1;
		}
	}
	if(cur) a[n++] = cur;
	return;
} 
void input(){
	read(0, buf, kI);
	char *cur = buf;
	la = cur;
	while(*cur >= '0') ++cur;
	ra = cur;
	while(*cur <  '0') ++cur;
	lb = cur;
	while(*cur >= '0') ++cur;
	rb = cur;

	calc(N, la, ra, A);
	calc(M, lb, rb, B);
}

void solve(){
	int K = (N + M == 2 ? 2 : 2 << (31 - __builtin_clz(N + M - 2)));
	build(K);
	NTT(K, A);
	NTT(K, B);
	for(int i = 0; i < K; ++i) C[i] = mul(A[i], B[i]);
	reverse(W + 1, W + K);
	NTT(K, C);

	ull R = mow(K, MOD - 2);
	for(int i = 0; i < K; ++i) C[i] = mul(C[i], R);
}

void ouput(){
	int pos = 0;
	for(; pos < N + M + 2; ++pos){
		ull v = C[pos] / kC;
		C[pos+1] += v;
		C[pos] -= v * kC;
	}
	while(!C[pos]) --pos;

	char *fub = buf;
	for(int i = 0; i < pos; ++i){
		for(int j = 0; j < 6; ++j){
			*fub = C[i] % 10 + '0';
			C[i] /= 10;
			++fub;
		}
	}
	while(C[pos]){
		*fub = C[pos] % 10 + '0';
		C[pos] /= 10;
		++fub;
	}
	reverse(buf, fub);
	write(1, buf, fub - buf);
}

int32_t main(){
	input();
	solve();
	ouput();
	return 0;
}
