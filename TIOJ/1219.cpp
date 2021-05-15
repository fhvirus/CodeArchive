// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[7122]; int OP;
inline char RC(){static char buf[7122],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,7122))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>7122)write(1,OB,OP),OP=0;}
inline int min(int a, int b){ return a < b ? a : b;}
const int N = 50005;

char mu[N];

signed main(){
	mu[1] = 1;
	for(int i = 2; i < N; ++i){
		if(mu[i]) continue;
		for(int j = i; j < N; j += i)
			++mu[j];
	}
	for(int i = 2; i * i < N; ++i)
		for(int j = i * i; j < N; j += i * i)
			mu[j] = 0;
	for(int i = 2; i < N; ++i) mu[i] = mu[i-1] + (mu[i] == 0 ? 0 : ((mu[i] & 1) ? -1 : 1));

	int a, b, d, ans;
	while(a = R(), b = R(), d = R()){
		ans = 0;

		a /= d, b /= d;

		int l = 1, r, u, v;
		for(; l <= a and l <= b; l = r + 1){
			u = a / l, v = b / l;
			r = min(a / u, b / v);
			ans += (mu[r] - mu[l-1]) * u * v;
		}

		W(ans);
	}
	
	write(1,OB,OP);
	return 0;
}