#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#include<algorithm>

const __int128 M1 = 1231453023109121ll;
const __int128 M2 = 1337006139375617ll;
const __int128 M  = M1 * M2;
const __int128 G  = 3;
inline __int128 modmul(__int128 a, __int128 b, const __int128 m){
	__int128 q = ((long double)(a)*b)/m + .5;
	__int128 r = (a*b - m*q) % m;
	return r < 0 ? r + m : r;
}
inline __int128 modpow(__int128 x, __int128 e, const __int128 m){
	__int128 r = 1;
	while(e) (e&1)&&(r=r*x%m), x=x*x%m, e>>=1;
	return r;
}
#define lg(n) 31 - __builtin_clz(n)

const __int128 BASE 	= 1000000000000;
const __int128 BASE_LEN = 12;
const int N = 1<<20;

int rev[N];
inline void init(int n){
	int l = lg(n), hb = -1;
	rev[0] = 0;
	for(int i = 1; i < n; ++i){
		if((i & (i-1)) == 0) ++hb;
		rev[i] = rev[i ^ (1<<hb)] | 1<<(l - hb - 1);
	}
}
inline void NTT1(__int128 A[], int n, bool inv){
	for(int i = 0; i < n; ++i) if(i < rev[i]) std::swap(A[i], A[rev[i]]);

	__int128 w, u, a, b;
	for(int len = 1; len < n; len <<= 1){
		w = modpow(G, (M1-1)/(len<<1), M1);
		if(inv) w = modpow(w, M1-2, M1);
		for(int group = 0; group < n; group += len<<1){
			u = 1;
			for(int i = 0; i < len; ++i){
				a = A[i + group];
				b = A[i + group + len] * u % M1;
				A[i + group] = (a+b < M1 ? a+b : a+b-M1);
				A[i + group + len] = (a-b < 0 ? a-b+M1 : a-b);
				u = u * w % M1;
			}
		}
	}
	if(inv){
		u = modpow(n, M1-2, M1);
		for(int i = 0; i < n; ++i)
			A[i] = A[i] * u % M1;
	}
}
inline void NTT2(__int128 A[], int n, bool inv){
	for(int i = 0; i < n; ++i) if(i < rev[i]) std::swap(A[i], A[rev[i]]);

	__int128 w, u, a, b;
	for(int len = 1; len < n; len <<= 1){
		w = modpow(G, (M2-1)/(len<<1), M2);
		if(inv) w = modpow(w, M2-2, M2);
		for(int group = 0; group < n; group += len<<1){
			u = 1;
			for(int i = 0; i < len; ++i){
				a = A[i + group];
				b = A[i + group + len] * u % M2;
				A[i + group] = (a+b < M2 ? a+b : a+b-M2);
				A[i + group + len] = (a-b < 0 ? a-b+M2 : a-b);
				u = u * w % M2;
			}
		}
	}
	if(inv){
		u = modpow(n, M2-2, M2);
		for(int i = 0; i < n; ++i)
			A[i] = A[i] * u % M2;
	}
}

char buf[1<<23];
int p;
__int128 a1[N], a2[N];
__int128 b1[N], b2[N];
__int128 c[N], c1[N], c2[N];
int a_digits, b_digits;
int main(){
	/*		count digits		*/
	fread(buf, 1, 1<<23, stdin);
	p = 0;
	while(buf[p] >= '0' and buf[p] <= '9') ++p;
	a_digits = p;
	while(buf[p] < '0' or buf[p] > '9') ++p;
	b_digits = p;
	while(buf[p] >= '0' and buf[p] <= '9') ++p;
	b_digits = p - b_digits;
	// printf("%d %d\n", a_digits, b_digits);


	/*		parser & save 		*/
	const int a_blocks = a_digits / BASE_LEN;
	const int a_left = a_digits % BASE_LEN;
	const int b_blocks = b_digits / BASE_LEN;
	const int b_left = b_digits % BASE_LEN;
	const int total_len = 1<<(lg(a_blocks+b_blocks+(a_left!=0)+(b_left!=0))+1);
	// printf("%d %d %d %d\n", a_blocks, a_left, b_blocks, b_left);
	p = 0;
	for(int i = 0; i < a_left; ++i)
		a1[a_blocks] = a1[a_blocks] * 10 + (buf[p++] - '0');
	for(int i = a_blocks - 1; i >= 0; --i)
		for(int j = 0; j < BASE_LEN; ++j)
			a1[i] = a1[i] * 10 + (buf[p++] - '0');
	// for(int i = 0; i <= a_blocks; ++i)
	// 	printf("%lld ", a[i]);
	// puts("");

	while(buf[p] < '0' or buf[p] > '9') ++p;

	for(int i = 0; i < b_left; ++i)
		b1[b_blocks] = b1[b_blocks] * 10 + (buf[p++] - '0');
	for(int i = b_blocks - 1; i >= 0; --i)
		for(int j = 0; j < BASE_LEN; ++j)
			b1[i] = b1[i] * 10 + (buf[p++] - '0');
	// for(int i = 0; i <= b_blocks; ++i)
	// 	printf("%lld ", b[i]);
	// puts("");


	/*		NTT & mult		*/
	init(total_len);
	for(int i = 0; i < total_len; ++i){
		a2[i] = a1[i];
		b2[i] = b1[i];
	}

	NTT1(a1, total_len, false);
	NTT1(b1, total_len, false);
	for(int i = 0; i < total_len; ++i)
		c1[i] = modmul(a1[i], b1[i], M1);
	NTT1(c1, total_len, true);


	NTT2(a2, total_len, false);
	NTT2(b2, total_len, false);
	for(int i = 0; i < total_len; ++i)
		c2[i] = modmul(a2[i], b2[i], M2);
	NTT2(c2, total_len, true);

	const __int128 money1 = 1ll * M1 * modpow(M1, M2-2, M2);
	const __int128 money2 = 1ll * M2 * modpow(M2, M1-2, M1);

	for(int i = 0; i < total_len; ++i)
		c[i] = (modmul(c1[i], money2, M) +
				modmul(c2[i], money1, M)) % M;

	/*		calc carry		*/
	__int128 carry = 0;
	for(int i = 0; i < total_len; ++i){
		c[i] += carry;
		carry = c[i] / BASE;
		c[i] %= BASE;
	}
	// for(int i = 0; i < total_len; ++i)
	// 	printf("%lld ", c[i]);
	// puts("");

	int jizz = total_len-1;
	while(c[jizz] == 0) --jizz;

	p = 0;
	for(int i = 0; i < jizz; ++i){
		for(int j = 0; j < BASE_LEN; ++j){
			buf[p++] = c[i]%10+'0';
			c[i] /= 10;
		}
	}
	while(c[jizz]){
		buf[p++] = c[jizz]%10+'0';
		c[jizz] /= 10;
	}
	std::reverse(buf, buf + p);
	fwrite(buf, 1, p, stdout);
}