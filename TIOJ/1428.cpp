// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<vector>
using namespace std;
const int N = 151, M = 1e9 + 9;

inline void madd(int &a, int b){
	a += b - M;
	a += (a >> 31) & M;
}

struct mat{
	int n;
	int v[N][N];
	mat(){}
	mat(int _n){
		n = _n;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				v[i][j] = 0;
	}
	void toI(int _n){
		n = _n;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				v[i][j] = (i == j);
	}
	void add(int i, int j){ v[i][j]++;}
	mat operator*(const mat &r) {
		mat ans(n);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j){
				for(int k = 0; k < n; ++k)
					madd(ans.v[i][j], 1ll * v[i][k] * r.v[k][j] % M);
			}
		return ans;
	}
};

mat mow(mat x, int e){
	mat r; r.toI(x.n);
	while(e){
		if(e & 1) r = r * x;
		x = x * x;
		e >>= 1;
	}
	return r;
}

int main(){
	int n, m, q, l;
	n = R(), m = R(), q = R(), l = R();
	mat in(n);
	for(int a, b; m; --m){
		a = R(), b = R();
		in.add(a, b);
	}
	in = mow(in, l);
	for(int a, b; q; --q){
		a = R(), b = R();
		W(in.v[a][b]);
	}
	write(1,OB,OP);
	return 0;
}
