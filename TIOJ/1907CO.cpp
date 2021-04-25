#pragma GCC target("avx2")
#pragma Ofast
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0'&&c!=EOF) c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}

#include<algorithm>
unsigned short lis[20000], t, m, p;

struct doll{
	unsigned short w, h;
} d[20000];

int main(){
	t = R();
	for(;t;--t){
		m = R();
		for(int i = 0; i < m; i++) d[i].w = R(), d[i].h = R();
		std::sort(d, d + m, [](doll a, doll b){
			return (a.w != b.w) ? a.w < b.w : a.h > b.h;
		});
		lis[0] = d[0].h;
		p = 1;
		for(int i = 1; i < m; i++)
			(d[i].h > lis[p-1] ? lis[p++] : *std::lower_bound(lis, lis+p, d[i].h)) = d[i].h;
		printf("%d\n", p);
	}
	return 0;
}