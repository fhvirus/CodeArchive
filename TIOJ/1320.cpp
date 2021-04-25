#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,j,n) for(int i=j;i<n;++i)
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

const int MAXN = 5e5+10, INF = 2147483647;
int n;
struct tower{
	int h, id;
	bool operator<(const tower &rhs) const{
		return h == rhs.h ? id < rhs.id : h > rhs.h;
	}
} T[MAXN];
struct seg{
	int l, r;
	bool operator<(const seg &rhs) const{
		return l == rhs.l ? r < rhs.r : l < rhs.l;
	}
};

int main(){
	n = R();
	for(int i = 0, h; i < n; ++i){
		h = R();
		T[i] = (tower){h, i};
	}
}