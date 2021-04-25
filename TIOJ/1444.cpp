#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
inline char readchar(){
	const int S = 1<<18;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline short R(){
	short ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

const short N = 5001;
short n, m;
short maxD[N], maxP[N];
short subD[N], subP[N];

void update(short u, short v, short d){
	if(maxD[u] < d){
		subD[u] = maxD[u]; maxD[u] = d;
		subP[u] = maxP[u]; maxP[u] = v;
	}
	else if(subD[u] < d)
		subD[u] = d; subP[u] = v;
}

short from[N<<1], to[N<<1], head[N<<1], prv[N<<1];
void dfs(short u, short p){
	for(short v = head[u]; v != -1; v = prv[v])
		if(to[v] != p)
			dfs(to[v], u), update(u, to[v], maxD[to[v]]+1);
}

void dfs2(short u, short p){
	if(p != 0)
		update(u, p, maxP[p] == u ? subD[p]+1 : maxD[p]+1);
	for(short v = head[u]; v != -1; v = prv[v])
		if(to[v] != p)
			dfs2(to[v], from[v]);
}

int main(){
	n = R(); m = R();

	for(int i = 0; i < N<<1; ++i) head[i] = -1;
	for(int a, b, i = 0; m; --m){
		a = R(); b = R();
		from[i] = a, to[i] = b;
		prv[i] = head[a]; head[a] = i++;
		from[i] = b, to[i] = a;
		prv[i] = head[b]; head[b] = i++;
	}

	dfs(1, 0); dfs2(1, 0);

	short mn = 32767, mx = 0;
	for(int i = 1; i <= n; ++i)
		(mn > maxD[i]) && (mn = maxD[i]),
		(mx < maxD[i]) && (mx = maxD[i]);
	for(int i = 1; i <= n; ++i)
		if(maxD[i] == mn) printf("%d ", i);
	printf("\n");
	for(int i = 1; i <= n; ++i)
		if(maxD[i] == mx) printf("%d ", i);
	printf("\n");
}