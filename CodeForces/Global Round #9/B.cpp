#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

int T, n, m, g;
bool can;
int main(){
	for(T = R(); T; --T){
		can = true;
		n = R(); m = R();
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < m; ++j){
				g = R();
				if(i==0||j==0||i==n-1||j==m-1){
					if((i==0||i==n-1)and(j==0||j==m-1)){
						if(g > 2) can = false;
					}else{
						if(g > 3) can = false;
					}
				}else{
					if(g > 4) can = false;
				}
			}
		}
		if(can){
			puts("YES");
			for(int i = 0; i < n; ++i){
				for(int j = 0; j < m; ++j){
					if(i==0||j==0||i==n-1||j==m-1){
						if((i==0||i==n-1)and(j==0||j==m-1))
							printf("2 ");
						else
							printf("3 ");
					}else{
						printf("4 ");
					}
				}
				printf("\n");
			}
		}
		else{
			puts("NO");
		}
	}
}