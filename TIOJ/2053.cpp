#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(long long n){char OB[20],OP=0,buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

typedef long long ll;
const int M = 1e9+7;
inline void mul(ll a[2][2], ll b[2][2], ll c[2][2]){
	c[0][0] = (a[0][0] * b[0][0] % M + a[0][1] * b[1][0] % M) % M;
	c[0][1] = (a[0][0] * b[0][1] % M + a[0][1] * b[1][1] % M) % M;
	c[1][0] = (a[1][0] * b[0][0] % M + a[1][1] * b[1][0] % M) % M;
	c[1][1] = (a[1][0] * b[0][1] % M + a[1][1] * b[1][1] % M) % M;
}


long long x1, x2, a, b, n;

long long mat[31][2][2], jizz[2][2] = {1, 0, 0, 1}, eek[2][2];

int main(){
	x1 = R(), x2 = R(), a = R(), b = R(), n = R()-2;
	mat[0][0][0] = b;
	mat[0][0][1] = a;
	mat[0][1][0] = 1;
	mat[0][1][1] = 0;
	for(int i = 1; i < 31; ++i){
		mul(mat[i-1], mat[i-1], mat[i]); 
	}

	for(ll i = 0; 1<<i <= n; ++i){
		if((1<<i) & n){
			mul(mat[i], jizz, eek);
			jizz[0][0] = eek[0][0] % M;
			jizz[0][1] = eek[0][1] % M;
			jizz[1][0] = eek[1][0] % M;
			jizz[1][1] = eek[1][1] % M;
		}
	}

	W((eek[0][0] * x2 % M + eek[0][1] * x1 % M) % M);
}