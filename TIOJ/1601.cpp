#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'&&c!=-1);if(c==-1)return 0;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];if(OP>65516)write(1,OB,OP),OP=0;}


#define MAXN 401
int n, m, match[MAXN], vis[MAXN], t, c, T, ans;
short to[160000];
int head[401], prv[160000];

inline void init(){
	t = 0;
	for(int i = 1; i <= n+m; ++i){
		match[i] = 0;
		vis[i] = 0;
		head[i] = -1;
	}
}

bool dfs(int u){
	if(vis[u] == t) return false;
	vis[u] = t;
	for(int v = head[u]; v != -1; v = prv[v]){
		if(!match[to[v]] or dfs(match[to[v]])){
			match[u] = to[v];
			match[to[v]] = u;
			return true;
		}
	}
	return false;
}

int main(){
	while(true){
		n = R(); m = R();
		if(n==0 and m==0) break;
		init();
		for(int i = 1, k = 0; i <= n; ++i){
			for(int j = 1; j <= m; ++j){
				c = R();
				if(c == 0){
					to[k] = j+n;
					prv[k] = head[i]; head[i] = k++;
				}
			}
		}
		ans = 0;
		for(int i = 1; i <= n; ++i){
			if(!match[i]){
				++t;
				ans += dfs(i);
			}
		}
		OB[OP++] = 'C';
		OB[OP++] = 'a';
		OB[OP++] = 's';
		OB[OP++] = 'e';
		OB[OP++] = ' ';
		W(++T);
		OB[OP++] = ':';
		OB[OP++] = ' ';
		W((n + m - ans)*2);
		OB[OP++] = '\n';
	}
	write(1,OB,OP);
	return 0;
}