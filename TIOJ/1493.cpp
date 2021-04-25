#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n, char e){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=e;if(OP>65516)write(1,OB,OP),OP=0;}
inline char RCMD(){ static char c; while((c=RC())!='G'&&c!='D'&&c!='Q');return c;}
inline void eek(){ OB[OP++]='E'; OB[OP++]='r'; OB[OP++]='r'; OB[OP++]='o'; OB[OP++]='r'; OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}


const int N = 1e6 + 1;
int n, m;
int head[N], to[N*2], prv[N*2];
int in[N], out[N], t = 1;
bool isleaf[N];
void dfs(int u, int p){
	in[u] = t++;
	for(int v = head[u]; v != -1; v = prv[v])
		if(to[v] != p) dfs(to[v], u);
	out[u] = t;
	if(in[u] + 1 == out[u]) isleaf[u] = true;
}

struct bit{
	int val[N];
	inline void modify(int p, int v){
		for(; p <= N; p += p & -p) val[p] += v;
	}
	inline int query(int p){
		int ans = 0;
		for(; p > 0; p -= p & -p) ans += val[p];
		return ans;
	}
	inline int query(int l, int r){ // [l, r)
		return query(r - 1) - query(l - 1);
	}
} tree[3];

int main(){
	n = R();
	for(int i = 1; i <= n; ++i)
		head[i] = -1;
	for(int i = 1, a, b, j = 0; i < n; ++i){
		a = R(), b = R();
		to[j] = b, prv[j] = head[a], head[a] = j++;
		to[j] = a, prv[j] = head[b], head[b] = j++;
	}
	dfs(1, 0);
	m = R();
	char cmd; int w, k, c;
	for(; m; --m){
		cmd = RCMD();
		if(cmd == 'G'){
			w = R(), k = R(), c = R();
			if(((k == 0 or k == 1) and w == 1) or
				(k == 2 and out[w] - in[w] == 1)){
				eek();
			}else{
				tree[k].modify(in[w], c);
			}
		} else if(cmd == 'D'){
			w = R(), k = R(), c = R();
			if(tree[k].query(in[w], in[w] + 1) < c) eek();
			else tree[k].modify(in[w], -c);
		} else if(cmd == 'Q'){
			w = R();
			W(tree[0].query(in[w], out[w]), ' ');
			W(tree[1].query(in[w], out[w]), ' ');
			W(tree[2].query(in[w], out[w]), '\n');
		}
	}
	write(1,OB,OP);
	return 0;
}