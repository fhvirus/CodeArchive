#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
inline char readchar(){
	const int S = 1<<18;
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
// Mimi : 0, Moumou : 1
inline bool name(){
	char c = readchar();
	while(c != 'M') c = readchar();
	return readchar() == 'o';
}

short n, a, b, quota[10001], u;
bool ans[10001];

short to[100000];
int e, head[10001], prv[100000];

short q[10010], h, t;

int main(){
	while(true){
		n = R();
		if(n == 0) break;
		for(int i = 0; i <= n; ++i){
			quota[i] = 0;
			ans[i] = 0;
			head[i] = -1;
		}
		e = R();
		for(int i = 0; i < e; ++i){
			a = R(); b = R();
			++quota[a];
			to[i] = a; prv[i] = head[b]; head[b] = i;
		}
		h = 0, t = 1, q[0] = n;
		ans[n] = 0;
		while(t > h){
			u = q[h++];
			if(u == 1) break;
			for(int v = head[u]; v != -1; v = prv[v]){
				!ans[u] and (ans[to[v]] = true);
				if(--quota[to[v]] == 0) q[t++] = to[v];
			}
		}
		puts((ans[1] ^ name()) ? "Moumou" : "Mimi");
	}
	return 0;
}