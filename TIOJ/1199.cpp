#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
typedef long long ll;
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

int a, n, y, eek;

inline int p(int x, int e){
	int ans = 1;
	while(e) (e&1)&&(ans=ans*x%y), x=x*x%y, e>>=1;
	return ans;
}

int main(){
	while(true){
		a = R(), n = R(), y = R();
		if(a == 0 and n == 0 and y == 0) return 0;
		if(n == 0){
			if(a == 1 or (y == 1 and a == 0)) printf("%d\n", y-1);
			else puts("0");
		} else {
			eek = 0;
			if(a == 0) eek++;
			int i;
			if(((a&1) and (y&1)) or (!(a&1) and !(y&1))) i = 2;
			else i = 1;
			for(; i < y; i += 2){
				if(p(i, n) == a) eek++;
			}
			printf("%d\n", eek);
		}
	}
}