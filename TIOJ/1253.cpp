#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define readchar getchar_unlocked
inline short R(){
	short ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
inline void W(int n){
    int N = n, rev, count = 0;
    rev = N;
    if (N == 0) { putchar_unlocked('0'); return ;}
    while ((rev % 10) == 0) { count++; rev /= 10;} //obtain the count of the number of 0s
    rev = 0;
    while (N != 0) { rev = (rev<<3) + (rev<<1) + N % 10; N /= 10;}  //store reverse of N in rev
    while (rev != 0) { putchar_unlocked(rev % 10 + '0'); rev /= 10;}
    while (count--) putchar_unlocked('0');
}

#define MAXN 2001
#define N 20000
short match[MAXN], vis[MAXN];
short n, k, t, T;
short to[N<<1], head[MAXN], prv[N<<1];

bool dfs(short u){
	if(vis[u] == t) return false;
	vis[u] = t;
	for(short v = head[u]; v != -1; v = prv[v])
		if(!match[to[v]] or dfs(match[to[v]])){
			match[u] = to[v];
			match[to[v]] = u;
			return true;
		}
	return false;
}

int main(){
	short ans;
	while(true){
		n = R(); k = R();
		if(n==0 and k==0) break;
		for(int i = 1; i <= n; ++i){
			match[i] = match[i + n] = 0;
			vis[i] = vis[i + n] = 0;
		}
		for(short i = 0; i < k<<1; ++i) head[i] = -1;
		for(short i = 0, r, c;k;--k){
			r = R(); c = R();
			to[i] = c+n;
			prv[i] = head[r]; head[r] = i++;
			to[i] = r;
			prv[i] = head[c+n]; head[c+n] = i++;
		}
		ans = 0;
		for(short i = 1; i <= n; ++i){
			if(!match[i]){
				t++;
				ans += dfs(i);
			}
		}
		putchar_unlocked('C');
		putchar_unlocked('a');
		putchar_unlocked('s');
		putchar_unlocked('e');
		putchar_unlocked(' ');
		putchar_unlocked('#');
		W(++T);
		putchar_unlocked(':');
		W(ans);
		putchar_unlocked('\n');
	}
	return 0;
}