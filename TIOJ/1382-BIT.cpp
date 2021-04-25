#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'&&c!=-1);if(c==-1)return 0;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=' ';if(OP>65516)write(1,OB,OP),OP=0;}

const int N = 1e5 + 225;

int n, nxt[N], val[N];

/* Start BIT */
inline int search(int v){
	int sum = 0, p = 0;
	for(int i = 31 - __builtin_clz(n); i >= 0; --i){
		if(p + (1<<i) <= n and sum + val[p + (1<<i)] < v)
			p += 1<<i, sum += val[p];
	}
	return p + 1;
}
/* End BIT */

int main(){
	while(n = R(), n != 0){
		for(int i = 1; i <= n; ++i)
			val[i] = i & -i;
		int p = 0, sum = n;
		for(int i = 0; i < n; ++i)
			nxt[i] = R();
		for(int i = 0; i < n; ++i){
			p = (p + nxt[i] - 1) % sum;
			int jiz = search(p + 1);
			W(jiz);
			for(int p = jiz; p <= n; p += p & -p) --val[p];
			--sum;
		}
		OB[OP++] = '\n';
	}
	write(1,OB,OP);
	return 0;
}