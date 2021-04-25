#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int readint(){
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
inline int lg(int n){
	int ans = 30;
	while(1<<ans > n) --ans;
	return ans;
}

const int N = 5e5;
long long sum[N<<1];
int tag[N<<1], n;
void init(){
	for(int i = 0; i < n; ++i){
		sum[i+n] = readint();
	}
	for(int i = n-1; i > 0; --i){
		sum[i] = sum[i<<1] + sum[i<<1|1];
	}
}
void update(int p, long long v, int h){
	sum[p] += v<<h;
	if(p < n) tag[p] += v;
}
void push(int p){
	for(int h = lg(n), i; h >= 0; --h){
		i = p>>h;
		if(!tag[i>>1]) continue;
		update(i, tag[i>>1], h);
		update(i^1, tag[i>>1], h);
		tag[i>>1] = 0;
	}
}
void pull(int p){
	for(int h = 1; p > 1; p >>= 1, ++h)
		sum[p>>1] = sum[p^1] + sum[p] + (tag[p>>1]<<h);
}
void modify(int l, int r, long long v){
	int tl = l, tr = r, h = 0;
	push(l+n), push(r-1+n);
	for(l += n, r += n; l < r; l >>= 1, r >>= 1, ++h){
		if(l&1) update(l++, v, h);
		if(r&1) update(--r, v, h);
	}
	pull(tl+n), pull(tr-1+n);
}
long long query(int l, int r){
	long long ans = 0;
	push(l+n), push(r-1+n);
	for(l += n, r += n; l < r; l >>= 1, r >>= 1){
		if(l&1) ans += sum[l++];
		if(r&1) ans += sum[--r];
	}
	return ans;
}

int main(){
	n = readint();
	init();
	int q = readint();
	for(int v, x, y, k;q;--q){
		v = readint();
		if(v == 1){
			x = readint(), y = readint(), k = readint();
			modify(x-1, y, k);
		} else {
			x = readint(), y = readint();
			printf("%lld\n", query(x-1, y));
		}
	}
	return 0;
}