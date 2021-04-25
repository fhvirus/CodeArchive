#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
inline char readchar(){
	const int S = 1<<16;
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
char outbuf[1<<16];
int outp;
inline void W(int n){
	if(n == 0){ outbuf[outp++] = '0'; return;}
    int rev = n, count = 0;
    while((rev % 10) == 0){ count++; rev /= 10;}
    rev = 0;
    while(n != 0){ rev = (rev<<3) + (rev<<1) + n % 10; n /= 10;}
    while(rev != 0) { outbuf[outp++] = (rev % 10 + '0'); rev /= 10;}
    while(count--) outbuf[outp++] = '0';
    if(outp >= (1<<16) - 64){
    	fwrite(outbuf, 1, outp, stdout);
    	outp = 0;
    }
}
inline short min(short a, short b){
	return a < b ? a : b;
}

const int N = 10001;
int n, m, T, head[N], prv[200000];
short to[200000];

short pre[N], low[N], t, cuts;
bool isCut[N];
void dfs(int u, int p){
	pre[u] = low[u] = ++t;
	short cnt = 0, v;
	for(int i = head[u]; i != -1; i = prv[i]){
		v = to[i];
		if(pre[v] == 0){
			++cnt;
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if(low[v] >= pre[u]){
				isCut[u] = true;
			}
		} else if(pre[v] < pre[u] and v != p){
			low[u] = min(low[u], pre[v]);
		}
	}
	if(p == 0 and cnt == 1)
		isCut[u] = false;
	if(isCut[u]) cuts++;
}

int main(){
	int jizz = 1;
	while(true){
		n = R(); m = R();
		if(n == 0) break;
		cuts = 0; t = 0;
		for(int i = 1; i <= n; ++i){
			pre[i] = 0;
			isCut[i] = false;
			head[i] = -1;
		}
		for(int a, b, i = 0; m; --m){
			a = R(); b = R();
			to[i] = b; prv[i] = head[a]; head[a] = i++;
			to[i] = a; prv[i] = head[b]; head[b] = i++;
		}
		dfs(1, 0);
		outbuf[outp++] = 'C';
		outbuf[outp++] = 'a';
		outbuf[outp++] = 's';
		outbuf[outp++] = 'e';
		outbuf[outp++] = ' ';
		outbuf[outp++] = '#';
		W(jizz++);
		outbuf[outp++] = ':';
		// fprintf(stdout, "Case #%d:", jizz++);
		if(cuts == 0){
			// fputs("0 0\n", stdout);
				outbuf[outp++] = '0';
				outbuf[outp++] = ' ';
				outbuf[outp++] = '0';
				outbuf[outp++] = '\n';
		}
		else {
			W(cuts), outbuf[outp++] = ' ';
			// fprintf(stdout, "%d ", cuts);
			for(int i = 1; i <= n; ++i)
				if(isCut[i]) W(i), outbuf[outp++] = ' '; //fprintf(stdout, "%d ", i);
			// fputc('\n', stdout);
			outbuf[outp++] = '\n';
		}
	}
	fwrite(outbuf, 1, outp, stdout);
}