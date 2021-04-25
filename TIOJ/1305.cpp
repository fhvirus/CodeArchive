#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}
inline int RCMD(){
	char c = readchar();
	while(c < 'a') c = readchar();
	return c == 'i' ? 0 : (c == 'r' ? 1 : (c == 'a' ? 2 : 3));
}

#include<algorithm>
using namespace std;

const int N = 1e5+1;
int bit[N], sz;
bool has[N];
struct query{
	int cmd, x;
} Q[N];
int qptr;
int des[N], e;

inline void mod(int p, int v){
	for(; p < N; p += p & -p) bit[p] += v;
}
inline int query(int p){
	int ans = 0;
	for(; p > 0; p -= p & -p) ans += bit[p];
	return ans;
}
inline int search(int v){
	int p = 0, sum = 0;
	for(int i = 17; i >= 0; --i){
		if(p + (1<<i) < N and sum + bit[p + (1<<i)] < v)
			sum += bit[p + (1<<i)],
			p += 1<<i;
	}
	return p;
}

int main(){
	int s, x;
	while(true){
		s = RCMD(), x = R();
		if(s == 3) break;
		if(s == 0) Q[qptr++] = {0, x}, des[e++] = x;
		if(s == 1) Q[qptr++] = {1, x}, des[e++] = x;
		if(s == 2) Q[qptr++] = {2, x};
	}

	sort(des, des + e);
	e = unique(des, des + e) - des;

	for(int i = 0; i < qptr; ++i){
		auto q = Q[i];
		if(q.cmd == 0){
			q.x = lower_bound(des, des + e, q.x) - des + 1;
			if(!has[q.x])
				mod(q.x, 1), has[q.x] = true, ++sz;
		} else if(q.cmd == 1){
			q.x = lower_bound(des, des + e, q.x) - des + 1;
			if(has[q.x])
				mod(q.x, -1), has[q.x] = false, --sz;
		} else {
			if(q.x > sz or q.x < 1) puts("error");
			else printf("%d\n", des[search(q.x)]);
		}
	}
}