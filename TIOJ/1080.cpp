#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[390000],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,390000))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
#include<cstdio>
const int MAXN = 1e5 + 10;

int a[MAXN], tmp[MAXN];

long long ans;
int main(){
	int n, T = 1;
	while(true){
		n = R();
		if(n == 0) break;
		for(int i = 0; i < n; i++) a[i] = R();
		ans = 0;
		for(int len = 2; len>>1 <= n; len <<= 1){
			for(int l = 0, r = len, m = len>>1; m <= n; l += len, r += len, m += len){
				int lptr = l, rptr = m, ptr = l, rcnt = 0;
				while(lptr < m or (rptr < r and rptr < n)){
					if(lptr < m and (rptr >= r || rptr >= n || a[lptr] <= a[rptr])){
						tmp[ptr++] = a[lptr++];
						ans += rcnt;
					}
					else{
						tmp[ptr++] = a[rptr++];
						rcnt++;
					}
				}
			}
			for(int i = 0; i < n; ++i)
				a[i] = tmp[i];
		}
		printf("Case #%d: %lld\n", T++, ans);
	}
	return 0;
}