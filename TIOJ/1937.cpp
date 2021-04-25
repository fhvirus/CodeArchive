#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<18;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
// inline int R(){
// 	int ans=0, c=readchar();
// 	while(c<'0') c=readchar();
// 	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
// 	return ans;
// }
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(int n){
    if(n == 0) outbuf[outp++] = '0';
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = ' ';
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}
#include<vector>
using namespace std;

const int N = 2048;
int n;

struct matrix{
	int n;
	vector<vector<int>> a;
	inline void init(int _n){
		n = _n;
		a = vector<vector<int>>(n, vector<int>(n, 0));
	}
	inline void init(int _n, vector<vector<int>> o, int x, int y){
		n = _n;
		a = vector<vector<int>>(n, vector<int>(n));
		FOR(i, n) FOR(j, n) a[i][j] = o[i + x][j + y];
	}
	inline void input(const int n){
		FOR(i, n) FOR(j, n) a[i][j] = R();
	}
	inline void ouput(const int n){
		FOR(i, n){
			FOR(j, n) W(a[i][j]);
			outbuf[outp++] = '\n';
		}
	}
	matrix(){}
	matrix(int _n): n(_n), a(vector<vector<int>>(n, vector<int>(n, 0))){}
	matrix(int _n, vector<vector<int>> o, int x, int y){
		n = _n;
		a = vector<vector<int>>(n, vector<int>(n));
		FOR(i, n) FOR(j, n) a[i][j] = o[i + x][j + y];
	}
	inline matrix operator+(const matrix &rhs){
		matrix ans(n);
		FOR(i, n) FOR(j, n) ans.a[i][j] = a[i][j] + rhs.a[i][j];
		return ans;
	}
	inline matrix operator-(const matrix &rhs){
		matrix ans(n);
		FOR(i, n) FOR(j, n) ans.a[i][j] = a[i][j] - rhs.a[i][j];
		return ans;
	}
	matrix operator*(const matrix &rhs){
		if(n == 1){
			matrix ans(1);
			ans.a[0][0] = a[0][0] * rhs.a[0][0];
			return ans;
		}
		if(n <= 128){
			matrix ans(n);
			FOR(i, n) FOR(j, n) FOR(k, n)
				ans.a[i][j] += a[i][k] * rhs.a[k][j];
			return ans;
		}
		int s = n / 2;
		matrix A(s, a, 0, 0), B(s, a, 0, s), C(s, a, s, 0), D(s, a, s, s),
			   E(s, rhs.a, 0, 0), F(s, rhs.a, 0, s), G(s, rhs.a, s, 0), H(s, rhs.a, s, s);
		// return rhs;

		matrix M1 = (A + D) * (E + H);
		matrix M2 = (C + D) * E;
		matrix M3 = A * (F - H);
		matrix M4 = D * (G - E);
		matrix M5 = (A + B) * H;
		matrix M6 = (C - A) * (E + F);
		matrix M7 = (B - D) * (G + H);
		A = M1 + M4 - M5 + M7;
		B = M3 + M5;
		C = M2 + M4;
		D = M1 - M2 + M3 + M6;

		E.init(n);
		FOR(i, s) FOR(j, s) E.a[i][j] = A.a[i][j];
		FOR(i, s) FOR(j, s) E.a[i][j + s] = B.a[i][j];
		FOR(i, s) FOR(j, s) E.a[i + s][j] = C.a[i][j];
		FOR(i, s) FOR(j, s) E.a[i + s][j + s] = D.a[i][j];
		return E;
	}
} a, b, c;

int main(){
	int jizz = n = R();
	{
		int j = 1;
		for(; (1ll<<j) < n; ++j);
		n = (1ll<<j);
	}
	a.init(n), b.init(n);
	a.input(jizz), b.input(jizz);

	c = a * b; c.ouput(jizz);
	fwrite(outbuf, 1, outp, stdout);
}