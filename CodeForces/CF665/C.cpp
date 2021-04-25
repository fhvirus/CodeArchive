#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<20;
inline char readchar(){
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

#include<algorithm>
using namespace std;

const int N = 1e5+1;
inline int GCD(int a, int b){
	while(b){
		a %= b;
		swap(a, b);
	}
	return a;
}
inline int min(int a, int b){
	return a < b ? a : b;
}

int t, n, a[N], d[N], id[N], mn, jizz, tmp;
bool ans, eek;

int main(){
	t = R();
	for(; t; --t){
		n = R(); mn = 2147483647; ans = true; eek = false;
		FOR(i,n) d[i] = a[i] = R(), mn = min(mn, a[i]);
		sort(d, d + n);

		FOR(i,n){
			if(a[i] != d[i]){
				jizz = (eek ? GCD(jizz, a[i]) : a[i]);
				eek = true;
			}
		}
		if(!eek or jizz == mn){ puts("YES"); continue;}

		ans = false;
		FOR(i,n){
			if(a[i] == d[i]){
				tmp = GCD(jizz, a[i]);
				if(tmp > mn) jizz = tmp;
				if(tmp == mn){ ans = true;break;}
			}
		}

		puts(ans ? "YES" : "NO");
	}
}