#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}

#include<cstdio>

const int N = 40001;
int n, m, a, b;

int dsu[N<<1];
inline void init(){
	for(int i = 1; i <= n; ++i)
		dsu[i] = i, dsu[i+n] = i+n;
}
inline int Find(int a){
	return dsu[a] == a ? a : dsu[a] = Find(dsu[a]);
}
inline void Union(int a, int b){
	if((a = Find(a)) == (b = Find(b))) return;
	dsu[b] = a;
}

bool flag;
int main(){
	while(true){
		n = R(); m = R();
		if(n == 0) break;
		init();
		flag = true;
		for(; m; --m){
			a = R(); b = R();
			Union(a, b+n);
			Union(b, a+n);
		}
		for(int i = 1; i <= n; ++i)
			if(Find(i) == Find(i+n)){
				flag = false; break;
			}
		puts(flag ? "Yes" : "No");
	}
	return 0;
}