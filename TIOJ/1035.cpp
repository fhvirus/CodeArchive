#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include<iostream>
#include<algorithm>
using namespace std;

#define eek ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
const int64_t M = 998244353, G = 3, N = 1 << 17;
int rev[N];

inline int lg(int n){
	int ans = 30;
	while(1 << ans > n) --ans;
	return ans;
}
inline int64_t mpow(int64_t x, int64_t e){
	int r = 1;
	while(e) (e&1)&&(r = r * x % M), x = x * x % M, e >>= 1;
	return r;
}
void init(int n){
	rev[0] = 0;
	int hb = -1, l = lg(n);
	for(int i = 1; i < n; ++i){
		if(!(i&i-1))++hb;
		rev[i] = rev[i ^ 1<<hb] | 1 << l - hb - 1;
	}
}

void NTT(int64_t A[], int n, bool inv){
	for(int i = 0; i < n; ++i)
		if(i < rev[i]) swap(A[i], A[rev[i]]);
	int64_t a, b, w, u;
	for(int len = 1; len < n; len <<= 1){
		u = mpow(G, (M - 1) / (len<<1));
		if(inv) u = mpow(u, M-2);
		for(int g = 0; g < n; g += len<<1){
			w = 1;
			for(int i = 0; i < len; ++i){
				a = A[g + i];
				b = A[g + i + len] * w % M;
				A[g + i] = (a + b) % M;
				A[g + i + len] = (a - b + M) % M;
				w = w * u % M;
			}
		}
	}
	if(inv){
		u = mpow(n, M-2);
		for(int i = 0; i < n; ++i)
			A[i] = A[i] * u % M;
	}
}

void mul(int64_t A[], int64_t B[], int64_t C[], int n){
	NTT(A, n, false);
	NTT(B, n, false);
	for(int i = 0; i < n; ++i)
		C[i] = A[i] * B[i] % M;
	NTT(C, n, true);
}

int64_t A[N], B[N], C[N], ans[N];
int main(){eek
	string s, t;
	cin >> s >> t;
	int n = 1 << lg(s.size() + t.size()) + 1, S = s.size(), T = t.size();
	init(n);
	for(int c = 0; c < 10; ++c){
		for(int i = 0; i < n; ++i){
			A[i] = (i < S and s[i] == 'a' + c);
			B[i] = (i < T and t[T - i - 1] == 'a' + c);
		}
		mul(A, B, C, n);
		for(int i = 0; i < n; ++i){
			ans[i] += C[i];
		}
	}
	cout << *max_element(ans, ans + n);
	return 0;
}