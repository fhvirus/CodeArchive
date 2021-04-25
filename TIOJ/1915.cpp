#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(int n, char e){
    if(n == 0) outbuf[outp++] = '0';
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = e;
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}
#include<algorithm>
#include<vector>
#include<queue>
#include<utility>
#include<functional>
using namespace std;

#define N 500000
#define M 800000
#define pii pair<int, int>
int t, n, e, out[N], deg[N], idx[N];
bool vis[N];
int head[N], to[M<<1], prv[M<<1];
priority_queue<pii, vector<pii>, greater<pii>> pq;

int main(){
	for(t = R(); t; --t){
		n = R(), e = R();
		for(int i = 0; i < n; ++i){
			out[i] = 0;
			deg[i] = 0;
			head[i] = -1;
			vis[i] = false;
			idx[i] = i;
		}
		for(int i = 0, u, v, j = 0; i < e; ++i){
			u = R(), v = R();
			out[min(u, v)]++;
			deg[u]++, deg[v]++;
			to[j] = v; prv[j] = head[u]; head[u] = j++;
			to[j] = u; prv[j] = head[v]; head[v] = j++;
		}
		int outmax = 0;
		for(int i = 0; i < n; ++i)
			outmax = max(outmax, out[i]);
		W(outmax, ' ');

		outmax = 0; pq = {};
		for(int i = 0; i < n; ++i)
			pq.push({deg[i], i});
		while(true){
			while(!pq.empty() and vis[pq.top().second]) pq.pop();
			if(pq.empty()) break;
			int cur = pq.top().second; pq.pop();
			vis[cur] = true;
			outmax = max(outmax, deg[cur]);
			for(int v = head[cur]; v != -1; v = prv[v]){
				if(!vis[to[v]]){
					--deg[to[v]];
					pq.push({deg[to[v]], to[v]});
				}
			}
		}
		W(outmax, '\n');
	}
	fwrite(outbuf, 1, outp, stdout);
}