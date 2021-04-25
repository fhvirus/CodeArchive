#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar(); bool minus = false;
	while(c<'-') c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}
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
				for(int i = l; i < r; i++)
					a[i] = tmp[i];
			}
		}
		printf("Case #%d: %lld\n", T++, ans);
	}
	return 0;
}