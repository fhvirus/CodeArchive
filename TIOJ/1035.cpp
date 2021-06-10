#include<cstdio>
#include<algorithm>
using namespace std;
#define int64_t long long int
const int64_t M = 998244353, G = 3, N = 1<<19;

char s[N], t[N];
int rev[N];

inline int lg(int n){
	int ans = 30;
	while(1<<ans > n) --ans;
	return ans;
}
inline int64_t mpow(int64_t n, int e){
	int64_t r = 1;
	while(e) (e&1)&&(r=r*n%M), n=n*n%M, e>>=1;
	return r;
}
inline void init(int n){
	rev[0] = 0;
	int hb = -1, l = lg(n);
	for(int i = 1; i < n; ++i){
		!(i & i-1) and ++hb;
		rev[i] = rev[i ^ 1<<hb] | 1<<l-hb-1;
	}
}
inline void NTT(int64_t A[], int n, bool inv){
	for(int i = 0; i < n; ++i)
		if(i < rev[i]) swap(A[i], A[rev[i]]);
	int64_t a, b, u, w;
	for(int len = 1; len < n; len<<=1){
		u = mpow(G, (M-1)/(len<<1));
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
inline void mul(int64_t A[], int64_t B[], int64_t C[], int n){
	NTT(A, n, false);
	NTT(B, n, false);
	for(int i = 0; i < n; ++i)
		C[i] = A[i] * B[i] % M;
	NTT(C, n, true);
}


int64_t A[N], B[N], C[N], ans[N];
int main(){
	int S, T, k, n;
	scanf("%d %d %d", &S, &T, &k);
	n = 1 << lg(S + T) + 1;
	init(n);
	scanf("%s %s", s, t);
	// printf("%d %d %d\n", S, T, k);
	// printf("%s\n%s\n\n", s, t);
	reverse(t, t + T);
	// printf("%s\n\n", t);
	// bitmask
	char gene[4] = {'A', 'T', 'C', 'G'};
	for(int c = 0; c < 4; ++c){
		// printf("%c\n", gene[c]);
		for(int i = 0; i < S; ++i){
			if(s[i] == gene[c]){
				++A[max(i - k, 0)];
				--A[min(i + k + 1, S)];
			}
		}
		for(int i = 1; i < S; ++i){
			A[i] += A[i-1];
		}
		for(int i = 0; i < n; ++i){
			A[i] = i < S and A[i] > 0;

			// printf("%lld ", A[i]);
		}
		// printf("\n");
		for(int i = 0; i < n; ++i){
			B[i] = i < T and t[i]==gene[c];
			// printf("%lld ", B[i]);
		}
		// printf("\n");
		// mul
		mul(A, B, C, n);
		for(int i = 0; i < n; ++i){
			ans[i] += C[i];
			A[i] = 0;
			B[i] = 0;
			// printf("%lld ", C[i]);
		}
		// printf("\n\n");
	}
	int cnt = 0;
	for(int i = 0; i < n; ++i){
		// printf("%d ", ans[i]);
		cnt += ans[i] == T;
	}
	// printf("\n");
	printf("%d", cnt);
	return 0;
}
