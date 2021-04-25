#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar(); bool minus = false;
	while(c<'-') c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}
#include<cstdlib>
#define FOR(i, n) for(int i = 0; i < n; ++i)
const int N = 1024;
int T, n, A[N][N], B[N][N], C[N][N], L[N], R1[N], R2[N], R3[N];

int main(){
	srand(7122);
	T = R();
	for(; T; --T){
		n = R();
		FOR(i, n) FOR(j, n) A[i][j] = R();
		FOR(i, n) FOR(j, n) B[i][j] = R();
		FOR(i, n) FOR(j, n) C[i][j] = R();

		bool ans = true;
		FOR(i, n) L[i] = rand() % 101 + 1;
		// R1 = B * L
		FOR(i, n) R1[i] = 0;
		FOR(i, n) FOR(j, n) R1[i] += B[i][j] * L[j];
		// R2 = A * R1
		FOR(i, n) R2[i] = 0;
		FOR(i, n) FOR(j, n) R2[i] += A[i][j] * R1[j];
		// R3 = C * L
		FOR(i, n) R3[i] = 0;
		FOR(i, n) FOR(j, n) R3[i] += C[i][j] * L[j];
		// Check
		FOR(i, n) if(R3[i] != R2[i]){ ans = false; break;}
		puts(ans ? "Loli is god." : "QAQ!");
	}
}