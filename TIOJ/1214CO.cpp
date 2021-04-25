#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<18;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c < '0') c = readchar();
	while(c>='0') ans = ans * 10 + (c^'0'), c = readchar();
	return ans;
}

#define llu unsigned long long
const int N = 101, M = 1e9 + 7;

int n, s1[N], s2[N], c1, c2;
int head1[N], to1[N<<1], prv1[N<<1];
int head2[N], to2[N<<1], prv2[N<<1];
llu h1, h2;

inline int max(int a, int b){
	return a > b ? a : b;
}
int calc1(int u, int p){
	int sz = 1, mx = 1, tmp;
	for(int v = head1[u]; v != -1; v = prv1[v])
		if(to1[v] != p){
			tmp = calc1(to1[v], u);
			mx = max(mx, tmp);
			sz += tmp;
		}
	mx = max(mx, n - sz);
	s1[u] = mx;
	return sz;
}
int calc2(int u, int p){
	int sz = 1, mx = 1, tmp;
	for(int v = head2[u]; v != -1; v = prv2[v])
		if(to2[v] != p){
			tmp = calc2(to2[v], u);
			mx = max(mx, tmp);
			sz += tmp;
		}
	mx = max(mx, n - sz);
	s2[u] = mx;
	return sz;
}
llu hash1(int u, int p){
	llu ans = 131, tmp;
	for(int v = head1[u]; v != -1; v = prv1[v])
		if(to1[v] != p){
			tmp = hash1(to1[v], u);
			ans = (ans + tmp * tmp % M) % M;
		}
	return ans;
}
llu hash2(int u, int p){
	llu ans = 131, tmp;
	for(int v = head2[u]; v != -1; v = prv2[v])
		if(to2[v] != p){
			tmp = hash2(to2[v], u);
			ans = (ans + tmp * tmp % M) % M;
		}
	return ans;
}

int main(){
	while((n = R()) != 0){
		c1 = c2 = 1;
		for(int i = 1; i <= n; ++i)
			head1[i] = head2[i] = -1;

		for(int i = 1, a, b, j = 0; i < n; ++i)
			a = R(), b = R(),
			to1[j] = b, prv1[j] = head1[a], head1[a] = j++,
			to1[j] = a, prv1[j] = head1[b], head1[b] = j++;
		for(int i = 1, a, b, j = 0; i < n; ++i)
			a = R(), b = R(),
			to2[j] = b, prv2[j] = head2[a], head2[a] = j++,
			to2[j] = a, prv2[j] = head2[b], head2[b] = j++;

		calc1(1, 0), calc2(1, 0);
		for(int i = 1; i <= n; ++i)
			c1 = (s1[i] < s1[c1] ? i : c1),
			c2 = (s2[i] < s2[c2] ? i : c2);

		h1 = hash1(c1, 0), h2 = hash2(c2, 0);
		if(h1 == h2) puts("Same");
		else{
			for(int i = c2; i <= n; ++i)
				c2 = (s2[i] == s2[c2] ? i : c2);
			h2 = hash2(c2, 0);
			puts(h1 == h2 ? "Same" : "Different");
		}
	}
}